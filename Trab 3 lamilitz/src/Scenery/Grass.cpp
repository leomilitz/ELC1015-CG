#include "Grass.h"

Grass::Grass(Vector2 pos, float width, float height, float r, float g, float b, float speed, float speedMultiplier) {
   this->pos = pos;
   this->width = width;
   this->height = height;
   this->speed = speed;
   this->speedMultiplier = speedMultiplier;
   this->r = r; this->g = g; this->b = b;

   hasOvergrownGrass = false;
   if (ru.getRandomInt(0, 100) <= 20)
      hasOvergrownGrass = true;
}

void Grass::render(float fps) {
   CV::color(r,g,b);
   CV::rectFill(pos, Vector2(pos.x + width, pos.y - height));

   if (hasOvergrownGrass) {
      CV::line(pos.x + width*0.5, pos.y, pos.x + width*0.2, pos.y + height*0.8, 3);
      CV::line(pos.x + width*0.1, pos.y, pos.x + width, pos.y + height*0.5, 3);
      CV::line(pos.x + width*0.7, pos.y, pos.x + width*1.4, pos.y + height*0.4, 3);
      CV::line(pos.x, pos.y, pos.x - width*0.1, pos.y + height*0.3, 2);
      CV::line(pos.x + width*0.5, pos.y, pos.x + width*0.5, pos.y + height*0.4, 2);
   }

   pos.x -= speed*speedMultiplier/fps;
}

void Grass::setSpeedMultiplier(float multiplier) {
   speedMultiplier = multiplier;
}

float Grass::getWidth() { return width; }
