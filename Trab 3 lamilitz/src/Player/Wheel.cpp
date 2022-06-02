#include "Wheel.h"

Wheel::Wheel(int radius, int centerX, int centerY, int tireThickness) {
   this->radius = radius;
   this->centerX = centerX;
   this->centerY = centerY;
   this->tireThickness = tireThickness;
   this->speed = 0.03;
   this->angle = 0.01;
}

void Wheel::drawSpokes() {
   CV::color(0.5,0.5,0.5);
   CV::line(0, 0, cos(angle)*radius, sin(angle)*radius, 4);                         // 0 degrees
   CV::line(0, 0, cos(PI/4 + angle)*radius, sin(PI/4 + angle)*radius, 4);           // 45 degrees
   CV::line(0, 0, cos(PI/2 + angle)*radius, sin(PI/2 + angle)*radius, 4);           // 90 degrees
   CV::line(0, 0, cos(PI*3/4 + angle)*radius, sin(PI*3/4 + angle)*radius, 4);       // 135 degrees
   CV::line(0, 0, cos(PI + angle)*radius, sin(PI + angle)*radius, 4);               // 180 degrees
   CV::line(0, 0, cos(PI*5/4 + angle)*radius, sin(PI*5/4 + angle)*radius, 4);       // 225 degrees
   CV::line(0, 0, cos(PI*3/2 + angle)*radius, sin(PI*3/2 + angle)*radius, 4);       // 270 degrees
   CV::line(0, 0, cos(PI*7/4 + angle)*radius, sin(PI*7/4 + angle)*radius, 4);       // 315 degrees
   angle -= speed;
}

void Wheel::render() {
   CV::translate(centerX, centerY);
   drawSpokes();
   CV::color(0,0,0);
   CV::circle(0, 0, radius, 25, 10);
   CV::circle(0, 0, radius+1, 23, 9);
   CV::translate(0, 0);
}
