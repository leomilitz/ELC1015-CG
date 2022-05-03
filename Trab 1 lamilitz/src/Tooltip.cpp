#include "Tooltip.h"

Tooltip::Tooltip(Vector2* p1, Vector2* p2, const char* text, int width, int height,
                 int direction, bool visible, const char* btnText) {
   this->radius = 0;
   this->p1 = p1;
   this->p2 = p2;
   this->text = text;
   this->width = width;
   this->height = height;
   this->visible = visible;
   this->btnText = btnText;
   this->splitTooltipText();
   (direction != 1) ? this->direction = -1 : this->direction = direction;
}

Tooltip::Tooltip(Vector2* center, int radius, const char* text, int width, int height,
                 int direction, bool visible, const char* btnText) {
   this->p1 = center;
   this->text = text;
   this->width = width;
   this->height = height;
   this->radius = radius;
   this->visible = visible;
   this->btnText = btnText;
   this->splitTooltipText();
   (direction != 1) ? this->direction = -1 : this->direction = direction;
}

void Tooltip::renderTooltip(Vector2* posMouse, bool visible) {
   bool canDrawTooltip = false;
   int outline = 7;

   if (!radius && *posMouse >= *p1 && *posMouse <= *p2) {
      for (int i = 0; i < outline; i++) {
         float alpha = 1.0 - ((float) i/(outline));
         CV::color(1, 1, 1, alpha);
         CV::rect(p1->x-i, p1->y-i, p2->x+i, p2->y+i);
      }
      canDrawTooltip = true;
   }

   if (radius > 0 && p1->distance(*posMouse) <= radius) {
      for (int i = 0; i < outline; i++) {
         float alpha = 1.0 - ((float) i/(outline));
         CV::color(1, 1, 1, alpha);
         CV::circle(p1->x, p1->y, radius + i, 15);
      }
      canDrawTooltip = true;
   }

   if (visible) {
      if (!radius) {
         CV::color(0.8, 0.8, 0.8);
         CV::rectFill(p1->x-2, p1->y-2, p2->x+2, p2->y+2);
         CV::color(0.6, 0.6, 0.6);
         CV::rectFill(*p1, *p2);
         CV::text((p1->x + p2->x)/2 - (text.size()*CHARSIZE/2), (((p1->y + p2->y)/2) - (CHARSIZE/2) + 1), text.c_str());
      } else {
         CV::color(0.8, 0.8, 0.8);
         CV::circleFill(p1->x, p1->y, radius + 2, 15);
         CV::color(0.6, 0.6, 0.6);
         CV::circleFill(p1->x, p1->y, radius, 15);
         CV::color(1,1,1);
         CV::text(p1->x - radius/3, p1->y - radius/3, btnText.c_str());
      }
   }

   if (canDrawTooltip) drawTooltip(posMouse);
}

void Tooltip::drawTooltip(Vector2* posMouse) {
   CV::color(0.7, 0.7, 0.7);
   CV::rectFill(posMouse->x - direction*2, posMouse->y - direction*2, posMouse->x + (width + 2)*direction, posMouse->y + (height + 2)*direction);
   CV::color(0.5, 0.5, 0.5);
   CV::rectFill(posMouse->x, posMouse->y, posMouse->x - width, posMouse->y + height * direction);
   CV::color(1,1,1);
   int posY = 1;
   for (std::string txt : splitText) {
      CV::text(posMouse->x - width + TEXT_OFFSET_X, posMouse->y - TEXT_OFFSET_Y*posY, txt.c_str());
      posY++;
   }
}

void Tooltip::splitTooltipText() {
   std::string slice;
   std::stringstream ss(text);
   while (std::getline(ss, slice, '\n'))
      splitText.push_back(slice);
}
