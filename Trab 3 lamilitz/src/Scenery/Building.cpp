#include "Building.h"

Building::Building(float posX, float posY, float width, float height, float r, float g, float b, float speed) {
   this->posX     = posX;
   this->posY     = posY;
   this->width    = width;
   this->height   = height;
   this->speed    = speed;
   this->r = r; this->g = g; this->b = b;
   createWindows();
}

void Building::createWindows() {
   windowSpacing = width/8;
   windowWidth = (width - 5*windowSpacing)/4;
   windowHeight = windowWidth;

   for (int i = posY + windowSpacing + windowHeight; i < posY + height  - windowSpacing; i += windowHeight + windowSpacing) {
      for (int j = posX + windowSpacing; j < posX + width - windowSpacing; j += windowWidth + windowSpacing) {
         if (ru.getRandomInt(0, 100) <= 40)
            windows.push_back(new Vector2(j,i));
      }
   }
}

void Building::drawWindows(float fps) {
   CV::color(0.9686, 1, 0.3686);
   for (Vector2* w : windows) {
      CV::rectFill(w->x, w->y, w->x + windowWidth, w->y + windowHeight);
      w->x -= speed/fps;
   }
}

void Building::render(float fps) {
   CV::color(r-0.1,g-0.1,b-0.1);
   CV::rect(posX-1, posY, posX + width + 1, posY + height + 1);
   CV::color(r,g,b);
   CV::rectFill(posX, posY, posX + width, posY + height);
   drawWindows(fps);
   posX -= speed/fps;
}

int Building::getWidth() { return width; }
