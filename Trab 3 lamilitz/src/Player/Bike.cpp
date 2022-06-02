#include "Bike.h"

Bike::Bike(int length, int spawnX, int spawnY) {
   this->length = length;
   this->spawnX = spawnX;
   this->spawnY = spawnY;
   bodyThickness = 8;
   wheelRadius = length/6;
   bodyLength = length/3;
   wheels.push_back(new Wheel(wheelRadius, spawnX + wheelRadius, spawnY + wheelRadius));
   wheels.push_back(new Wheel(wheelRadius, spawnX + wheelRadius*5, spawnY + wheelRadius));
}

void Bike::render() {
   for (Wheel *w : wheels) w->render();

   CV::translate(spawnX + wheelRadius, spawnY + wheelRadius);
   CV::color(1,0,0);
   // Body
   float pedalX = bodyLength, pedalY = 0;
   CV::line(0, 0, wheelRadius, wheelRadius*4/3, bodyThickness); // 1
   CV::line(0, 0, bodyLength*3/4, 0, bodyThickness); // 2
   CV::line(wheelRadius, wheelRadius*4/3, wheelRadius + bodyLength, wheelRadius*2, bodyThickness); // 4
   CV::line(bodyLength*3/4, 0, wheelRadius, wheelRadius*4/3, bodyThickness); // 3
   CV::line(bodyLength*3/4, 0, wheelRadius + bodyLength, wheelRadius*2, bodyThickness); // 5
   CV::line(bodyLength + wheelRadius, wheelRadius*2, wheelRadius*4, 0, bodyThickness); // 6
   CV::circleFill(bodyLength*3/4, 0, 4, 20);

   // Seat
   float bancoX = 1.9*wheelRadius/3, bancoY = 7*wheelRadius/3;
   CV::line(wheelRadius, wheelRadius*4/3, bancoX, bancoY, bodyThickness);
   CV::color(0.2,0.2,0.2);
   CV::line(bancoX, bancoY, wheelRadius/3, bancoY, bodyThickness);
   CV::line(bancoX, bancoY, bancoX + wheelRadius/2, bancoY, bodyThickness);

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

   CV::translate(0,0);
}
