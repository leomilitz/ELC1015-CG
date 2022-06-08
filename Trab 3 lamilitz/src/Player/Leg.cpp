#include "Leg.h"

Leg::Leg(Stickman* stickman, Pedal* pedal, float legSize) {
   this->stickman = stickman;
   this->pedal = pedal;
   this->legSize = legSize;
   this->pedalSpeed = pedal->getSpeed();
   this->pedalLength = pedal->getLength();
   this->kneeAngle = 1.75*PI;
}

void Leg::render(float fps) {
   Vector2 seat = stickman->getSeatCoords();
   Vector2 feet = pedal->getPedalCoords();

   float kneeX = (seat.x + feet.x)*0.5 + legSize;
   float kneeY = (seat.y + feet.y)*0.5 + legSize*0.3;

   Vector2 knee = Vector2(kneeX, kneeY);

   CV::line(seat, knee, 10);
   CV::line(knee, feet, 10);
   CV::circleFill(knee, 5, 20);
}
