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

   float r1, r2;
   r1 = r2 = legSize*0.5;
   float d = feet.distance(seat);
   float l = (((r1*r1) - (r2*r2)) + (d*d))/(2*d);
   float h = sqrt((r1*r1) - (l*l));
   float kneeX = (l/d)*(feet.x - seat.x) - (h/d)*(feet.y - seat.y) + seat.x;
   float kneeY = (l/d)*(feet.y - seat.y) + (h/d)*(feet.x - seat.x) + seat.y;

   CV::color(0,0,0);
   Vector2 knee = Vector2(kneeX, kneeY);
   CV::line(seat, knee, 10);
   CV::line(knee, feet, 10);
   CV::circleFill(knee, 5, 20);
}
