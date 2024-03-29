#include "Bike.h"

Bike::Bike(int length, int posX, int posY) {
   this->length = length;
   this->posX = posX;
   this->posY = posY;
   bodyThickness = 8;
   wheelRadius = length/6;
   bodyLength = length/3;
   wheels.push_back(new Wheel(wheelRadius, posX + wheelRadius, posY + wheelRadius));
   wheels.push_back(new Wheel(wheelRadius, posX + wheelRadius*5, posY + wheelRadius));
   pedalFront = new Pedal(posX + 2.5*wheelRadius, posY + wheelRadius, wheelRadius*0.75, 1);
   pedalBack =  new Pedal(posX + 2.5*wheelRadius, posY + wheelRadius, wheelRadius*0.75, -1);
}

void Bike::render(float fps) {
   // Pedal Back
   pedalBack->render(fps);

   // Wheels
   for (Wheel *w : wheels) w->render(fps);

   CV::translate(posX + wheelRadius, posY + wheelRadius);
   CV::color(1,0,0);
   // Body
   CV::line(0, 0, wheelRadius, wheelRadius*4/3, bodyThickness); // 1
   CV::line(0, 0, bodyLength*0.75, 0, bodyThickness); // 2
   CV::line(wheelRadius, wheelRadius*4/3, wheelRadius + bodyLength, wheelRadius*2, bodyThickness); // 4
   CV::line(bodyLength*0.75, 0, wheelRadius, wheelRadius*4/3, bodyThickness); // 3
   CV::line(bodyLength*0.75, 0, wheelRadius + bodyLength, wheelRadius*2, bodyThickness); // 5
   CV::line(bodyLength + wheelRadius, wheelRadius*2, wheelRadius*4, 0, bodyThickness); // 6
   CV::circleFill(bodyLength*0.75, 0, 4, 20);

   // Seat
   float seatX = 1.9*wheelRadius/3, seatY = 7*wheelRadius/3;
   CV::line(wheelRadius, wheelRadius*4/3, seatX, seatY, bodyThickness);
   CV::color(0.2,0.2,0.2);
   CV::line(seatX, seatY, wheelRadius/3, seatY, bodyThickness);
   CV::line(seatX, seatY, seatX + wheelRadius/2, seatY, bodyThickness);

   // Handle
   float handleX = bodyLength + wheelRadius*2/3, handleY = wheelRadius*8/3;
   CV::color(1,0,0);
   CV::line(bodyLength + wheelRadius, wheelRadius*2, handleX, handleY, bodyThickness);
   CV::color(0.2,0.2,0.2);
   CV::line(handleX - wheelRadius/5, handleY, handleX + wheelRadius/2, handleY, bodyThickness);

   // Wheel Holders
   CV::color(0.6, 0.6, 0.6);
   CV::circleFill(0,0, wheelRadius/3, 15);
   CV::circleFill(wheelRadius*4, 0, wheelRadius/3, 15);
   CV::color(0.5, 0.5, 0.5);
   CV::circleFill(0,0, wheelRadius/4, 15);
   CV::circleFill(wheelRadius*4, 0, wheelRadius/4, 15);

   // Pedal Circle
   CV::color(0.2, 0.2, 0.2);
   CV::circleFill(wheelRadius*1.5, 0, wheelRadius*0.4, 15);
   CV::color(0.25, 0.25, 0.25);
   CV::circleFill(wheelRadius*1.5, 0, wheelRadius*0.32, 15);
   CV::translate(0,0);

   // Pedal Front
   pedalFront->render(fps);
   CV::translate(posX + wheelRadius, posY + wheelRadius);
   CV::color(0.1, 0.1, 0.1);
   CV::circleFill(wheelRadius*1.5, 0, wheelRadius*0.15, 15);
   CV::translate(0, 0);
}

void Bike::setSpeedMultiplier(float multiplier) {
   pedalBack->setSpeedMultiplier(multiplier);
   pedalFront->setSpeedMultiplier(multiplier);
   for (Wheel* w : wheels)
      w->setSpeedMultiplier(multiplier);
}

Pedal* Bike::getPedal(bool isFrontPedal) {
   if (isFrontPedal) return pedalFront;
   return pedalBack;
}

Vector2 Bike::getPedalCoords(bool isFrontPedal) {
   if (isFrontPedal) return pedalFront->getPedalCoords();
   return pedalBack->getPedalCoords();
}
