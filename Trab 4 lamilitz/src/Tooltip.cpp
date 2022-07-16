#include "Tooltip.h"

Tooltip::Tooltip(int x1, int y1, int x2, int y2, std::string text, int width, int directionV, int directionH, bool visible, std::string btnText)
:UIComponent(x1, y1, x2, y2, btnText, [](){})  {
   this->radius = 0;
   this->width = width;
   this->visible = visible;
   this->text = text;
   this->splitTooltipText();
   this->height = TEXT_OFFSET_Y*splitText.size()*1.2;
   this->isHovering = false;
   this->posMouse = new Vector2(0,0);
   this->type = tooltip;
   (directionV != 1) ? this->directionV = -1 : this->directionV = 1;
   (directionH != 1) ? this->directionH = -1 : this->directionH = 1;
}

Tooltip::Tooltip(int x, int y, int radius, std::string text, int width, int directionV, int directionH, bool visible, std::string btnText)
:UIComponent(x, y, 0, 0, btnText, [](){}) {
   this->width = width;
   this->radius = radius;
   this->visible = visible;
   this->text = text;
   this->splitTooltipText();
   this->height = TEXT_OFFSET_Y*splitText.size();
   this->isHovering = false;
   this->posMouse = new Vector2(0,0);
   this->type = tooltip;
   (directionV != 1) ? this->directionV = -1 : this->directionV = 1;
   (directionH != 1) ? this->directionH = -1 : this->directionH = 1;
}

void Tooltip::mouseInputManagement(int mouseX, int mouseY, int *mouseState, int button) {
   posMouse->x = mouseX; posMouse->y = mouseY;

   if (radius && pos1->distance(*posMouse) <= radius) {
      isHovering = true;
      return;
   }

   if (!radius && *posMouse >= *pos1 && *posMouse <= *pos2) {
      isHovering = true;
      return;
   }

   isHovering = false;
}

void Tooltip::render() {
   bool canDrawTooltip = false;
   int outline = 7;

   if (!radius && isHovering) {
      for (int i = 0; i < outline; i++) {
         float alpha = 1.0 - ((float) i/(outline));
         CV::color(1, 1, 1, alpha);
         CV::rect(pos1->x-i, pos1->y-i, pos2->x+i, pos2->y+i);
      }
      canDrawTooltip = true;
   }

   if (radius > 0 && isHovering) {
      for (int i = 0; i < outline; i++) {
         float alpha = 1.0 - ((float) i/(outline));
         CV::color(1, 1, 1, alpha);
         CV::circle(pos1->x, pos1->y, radius + i, 15);
      }
      canDrawTooltip = true;
   }

   if (visible) {
      if (!radius) {
         CV::color(0.8, 0.8, 0.8);
         CV::rectFill(pos1->x-2, pos1->y-2, pos2->x+2, pos2->y+2);
         CV::color(0.6, 0.6, 0.6);
         CV::rectFill(*pos1, *pos2);
         CV::text((pos1->x + pos2->x)/2 - (caption.size()*CHARSIZE/2), (((pos1->y + pos2->y)/2) - (CHARSIZE/2) + 1), caption.c_str());
      } else {
         CV::color(0.8, 0.8, 0.8);
         CV::circleFill(pos1->x, pos1->y, radius + 2, 15);
         CV::color(0.6, 0.6, 0.6);
         CV::circleFill(pos1->x, pos1->y, radius, 15);
         CV::color(1,1,1);
         CV::text(pos1->x - radius/3, pos1->y - radius/3, caption.c_str());
      }
   }

   if (canDrawTooltip) drawTooltip();
}

void Tooltip::drawTooltip() {
   CV::color(0.7, 0.7, 0.7);
   CV::rectFill(posMouse->x - directionH*2, posMouse->y - directionV*2, posMouse->x + (width + 2)*directionH, posMouse->y + (height + TEXT_OFFSET_Y) * directionV);
   CV::color(0.5, 0.5, 0.5);
   CV::rectFill(posMouse->x, posMouse->y, posMouse->x + width*directionH, posMouse->y + ((height + TEXT_OFFSET_Y) * directionV));
   CV::color(1,1,1);

   int posY;
   (directionV == 1) ? posY = splitText.size() : posY = 1;

   int posXOffset;
   (directionH == 1) ? posXOffset = 0 : posXOffset = -width;

   for (std::string txt : splitText) {
      CV::text(posMouse->x + TEXT_OFFSET_X + posXOffset, posMouse->y + directionV*TEXT_OFFSET_Y*posY, txt.c_str());
      (directionV == 1) ? posY-- : posY++;
   }
}

void Tooltip::splitTooltipText() {
   std::string slice;
   std::stringstream ss(text);
   while (std::getline(ss, slice, '\n'))
      splitText.push_back(slice);
}
