#include "Pedal.h"

Pedal::Pedal(int centerX, int centerY, float armLength, int orientation) {
   this->centerX = centerX;
   this->centerY = centerY;
   this->armLength = armLength;
   this->pedalX = 0;
   this->speed = 4;
   this->speedMultiplier = 1.0;
   switch (orientation) {
      case 1:     this->angle = PI*0.5;     break;
      default:    this->angle = PI*1.5;     break;
   }
}

void Pedal::render(float fps) {
   CV::color(0.15, 0.15, 0.15);

   pedalX = centerX + cos(angle)*armLength;
   pedalY = centerY + sin(angle)*armLength;
   CV::line(centerX, centerY, pedalX, pedalY, 6);
   CV::line(pedalX, pedalY, pedalX + armLength*0.2, pedalY, 5);
   CV::line(pedalX, pedalY, pedalX - armLength*0.2, pedalY, 5);
   angle -= speed*speedMultiplier/fps;
}

void Pedal::setSpeedMultiplier(float multiplier) {
   speedMultiplier = multiplier;
}

Vector2 Pedal::getPedalCoords() { return Vector2(pedalX, pedalY); }

float Pedal::getLength() { return armLength; }
