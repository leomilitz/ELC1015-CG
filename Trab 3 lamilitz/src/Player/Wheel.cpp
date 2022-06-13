#include "Wheel.h"

Wheel::Wheel(int radius, int centerX, int centerY, int tireThickness) {
   this->radius = radius;
   this->centerX = centerX;
   this->centerY = centerY;
   this->tireThickness = tireThickness;
   this->speed = 6;
   this->speedMultiplier = 1.0;
   this->angle = 0.01;
}

void Wheel::drawSpokes() {
   CV::color(0.7,0.7,0.7);

   for (float i=0; i <= 1.75; i+=0.25)
      CV::line(0, 0, cos(PI*i + angle)*radius, sin(PI*i + angle)*radius, 4);

   angle -= speed*speedMultiplier/fps;
}

void Wheel::render(float fps) {
   this->fps = fps;
   CV::translate(centerX, centerY);
   drawSpokes();
   CV::color(0,0,0);
   CV::circle(0, 0, radius, 25, 10);
   CV::circle(0, 0, radius+1, 23, 9);
   CV::translate(0, 0);
}

void Wheel::setSpeedMultiplier(float multiplier) {
   speedMultiplier = multiplier;
}

