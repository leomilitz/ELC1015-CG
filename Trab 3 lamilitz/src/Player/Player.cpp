#include "Player.h"

Player::Player(int width, int height, int posX, int posY) {
   this->width  = width;
   this->height = height;
   this->posX = posX;
   this->posY = posY;
   this->bike = new Bike(width, posX, posY);
   float radius = width/6, seatX = posX + radius + radius*1.9/3, seatY = posY + radius*0.1 + radius*10/3;
   this->stickman = new Stickman(seatX, seatY, radius, posX, posY);
   this->frontLeg = new Leg(stickman, bike->getPedal(true),  radius*3.5);
   this->backLeg  = new Leg(stickman, bike->getPedal(false), radius*3.5);
   this->showCalcs = false;
}

void Player::render(float fps) {
   CV::color(0.06,0.06,0.06);
   backLeg->render(fps);
   bike->render(fps);
   stickman->render(fps);
   CV::color(0,0,0);
   frontLeg->render(fps);

   if (showCalcs) {
      float legSize      = frontLeg->getLegSize()*0.5;
      Vector2 frontKnee  = frontLeg->getKneePosition();
      Vector2 backKnee   = backLeg->getKneePosition();
      Vector2 frontPedal = bike->getPedalCoords(true);
      Vector2 backPedal  = bike->getPedalCoords(false);
      Curve* c = stickman->getBackCoords();

      CV::color(1,1,0);
      Vector2* seatCoord = c->points[0];
      CV::circle(*seatCoord, legSize, 50);
      CV::circle(frontPedal, legSize, 50);
      CV::circle(frontKnee, legSize, 50);

      CV::color(0,0,1);
      CV::circleFill(frontKnee, 5, 15);
      CV::circleFill(backKnee, 5, 15);
      CV::circleFill(frontPedal, 5, 15);
      CV::circleFill(backPedal, 5, 15);
      for (Vector2* v : c->points) CV::circleFill(*v, 5, 15);
   }
}

void Player::showCalculations(bool showCalcs) {
   this->showCalcs = showCalcs;
}
