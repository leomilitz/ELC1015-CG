#include "Building.h"

Building::Building(float posX, float posY, float width, float height, float r, float g, float b, float speed) {
   this->posX     = posX;
   this->posY     = posY;
   this->width    = width;
   this->height   = height;
   this->r = r; this->g = g; this->b = b;
   this->speed = speed;
}

void Building::render() {
   CV::color(r,g,b);
   CV::rectFill(posX, posY, posX + width, posY + height);
   posX -= speed;
}

int Building::getWidth() { return width; }
