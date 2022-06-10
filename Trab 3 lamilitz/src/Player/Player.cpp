#include "Player.h"

Player::Player(int width, int height, int posX, int posY) {
   this->width  = width;
   this->height = height;
   this->posX = posX;
   this->posY = posY;
   this->bike = new Bike(width, posX, posY);
   float radius = width/6, seatX = posX + radius + radius*1.9/3, seatY = posY + radius + radius*7/3;
   this->stickman = new Stickman(seatX, seatY, radius, posX, posY);
   this->frontLeg = new Leg(stickman, bike->getPedal(true),  radius*3.5);
   this->backLeg  = new Leg(stickman, bike->getPedal(false), radius*3.5);
}

void Player::render(float fps) {
   CV::color(0.06,0.06,0.06);
   backLeg->render(fps);
   bike->render(fps);
   stickman->render(fps);
   CV::color(0,0,0);
   frontLeg->render(fps);
}
