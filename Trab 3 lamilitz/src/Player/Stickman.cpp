#include "Stickman.h"

Stickman::Stickman(int posX, int posY, float radius, int bikeX, int bikeY) {
   this->posX = posX;
   this->posY = posY;
   this->radius = radius;
   backCoords.push_back(Vector2(posX, posY));
   backCoords.push_back(Vector2(bikeX + 2*radius, bikeY + 5*radius));
   backCoords.push_back(Vector2(bikeX + 3*radius, bikeY + 5*radius));
   stkBack = new Curve(backCoords);
}

void Stickman::render() {
   stkBack->renderBezier(10);
}
