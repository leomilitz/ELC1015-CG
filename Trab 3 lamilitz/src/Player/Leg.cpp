#include "Leg.h"

Leg::Leg(Stickman* stickman, Pedal* pedal, float legSize) {
   this->stickman = stickman;
   this->pedal = pedal;
   this->legSize = legSize;
   this->pedalSpeed = pedal->getSpeed();
}

void Leg::render(float fps) {
   Vector2 seat = stickman->getSeatCoords();
   Vector2 feet = pedal->getPedalCoords();
}
