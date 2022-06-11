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
   CV::line(0, 0, cos(angle)*radius, sin(angle)*radius, 4);                         // 0 degrees
   CV::line(0, 0, cos(PI*0.25 + angle)*radius, sin(PI*0.25 + angle)*radius, 4);     // 45 degrees
   CV::line(0, 0, cos(PI*0.5 + angle)*radius, sin(PI*0.5 + angle)*radius, 4);       // 90 degrees
   CV::line(0, 0, cos(PI*0.75 + angle)*radius, sin(PI*0.75 + angle)*radius, 4);     // 135 degrees
   CV::line(0, 0, cos(PI + angle)*radius, sin(PI + angle)*radius, 4);               // 180 degrees
   CV::line(0, 0, cos(PI*1.25 + angle)*radius, sin(PI*1.25 + angle)*radius, 4);     // 225 degrees
   CV::line(0, 0, cos(PI*1.5 + angle)*radius, sin(PI*1.5 + angle)*radius, 4);       // 270 degrees
   CV::line(0, 0, cos(PI*1.75 + angle)*radius, sin(PI*1.75 + angle)*radius, 4);     // 315 degrees
   angle -= speed*speedMultiplier/fps;
}

void Wheel::setSpeedMultiplier(float multiplier) {
   speedMultiplier = multiplier;
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
