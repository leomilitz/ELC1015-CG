#include "Grass.h"

Grass::Grass(Vector2 pos, float width, float height, float r, float g, float b, float grassSpeed) {
   this->pos = pos;
   this->width = width;
   this->height = height;
   this->speed = grassSpeed;
   this->r = r; this->g = g; this->b = b;
}

void Grass::render(float fps) {
   CV::color(r,g,b);
   CV::rectFill(pos, Vector2(pos.x + width, pos.y - height));
   pos.x -= speed/fps;
}

float Grass::getWidth() { return width; }
