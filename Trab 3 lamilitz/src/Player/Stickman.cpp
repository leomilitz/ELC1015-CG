#include "Stickman.h"

Stickman::Stickman(int posX, int posY, float radius, int bikeX, int bikeY) {
   this->posX = posX;
   this->posY = posY;
   this->radius = radius;
   this->bikeX = bikeX;
   this->bikeY = bikeY;
   neck = new Vector2(bikeX + 3*radius, bikeY + 5*radius);
   backCoords.push_back(new Vector2(posX, posY));
   backCoords.push_back(new Vector2(bikeX + 2*radius, bikeY + 5*radius));
   backCoords.push_back(neck);
   stkBack = new Curve(backCoords);
}

void Stickman::render(float fps) {
   CV::color(0,0,0);
   stkBack->renderBezier(10);

   // Back Arm
   float handleX = bikeX + 3*radius + radius*2/3, handleY = bikeY + radius + radius*8/3;
   CV::color(0.06, 0.06, 0.06);
   CV::line(neck->x, neck->y, posX + radius*1.5, posY + radius*0.45, 10);
   CV::line(posX + radius*1.5, posY + radius*0.45, handleX, handleY, 10);

   // Front Arm
   CV::color(0,0,0);
   CV::line(neck->x, neck->y, posX + radius, posY + radius*0.4, 10);
   CV::circleFill(posX + radius, posY + radius*0.4, 5, 15);
   CV::line(posX + radius, posY + radius*0.4, handleX, handleY, 10);
   CV::circleFill(handleX, handleY, 5, 15);

   // Head
   CV::color(0,0,0);
   CV::circleFill(*neck + radius*0.3, radius*0.6, 25);
   CV::color(1,1,1);
   CV::circleFill(*neck + radius*0.3, radius*0.44, 25);

   // Eyes
   CV::color(0,0,0);
   CV::line(neck->x + radius*0.6, neck->y + radius*0.3, neck->x + radius*0.6, neck->y + radius*0.15, 5);
   CV::line(neck->x + radius*0.4, neck->y + radius*0.3, neck->x + radius*0.65, neck->y + radius*0.3, 6);
}

Vector2 Stickman::getSeatCoords() { return Vector2(posX, posY); }
