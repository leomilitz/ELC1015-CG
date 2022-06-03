#include "Player.h"

Player::Player(int width, int height, int posX, int posY) {
   this->width  = width;
   this->height = height;
   this->posX = posX;
   this->posY = posY;
   this->bike = new Bike(width, posX, posY);
   float radius = width/6, seatX = posX + radius + radius*1.9/3, seatY = posY + radius + radius*7/3;
   this->stickman = new Stickman(seatX, seatY, radius, posX, posY);
}

void Player::render() {
   // Placeholder
   CV::color(1,1,1);
   CV::translate(posX, posY);
   CV::rectFill(0,0, width, height);

   CV::color(0,0,1);
   for (int i = 0; i <= 6; i++)
      CV::line(i*width/6, 0, i*width/6, height);

   for (int i = 0; i <= 7; i++)
      CV::line(0, i*width/6, width, i*width/6);

   CV::translate(0,0);

   bike->render();
   stickman->render();
}
