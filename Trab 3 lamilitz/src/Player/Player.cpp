#include "Player.h"

Player::Player(int width, int height, int spawnX, int spawnY) {
   this->width  = width;
   this->height = height;
   this->spawnX = spawnX;
   this->spawnY = spawnY;
   this->bike = new Bike(width, spawnX, spawnY);
}

void Player::render() {
   // Placeholder
   CV::color(1,1,1);
   CV::translate(spawnX, spawnY);
   CV::rectFill(0,0, width, height);

   CV::color(0,0,1);
   for (int i = 0; i <= 6; i++)
      CV::line(i*width/6, 0, i*width/6, height);

   for (int i = 0; i <= 7; i++)
      CV::line(0, i*width/6, width, i*width/6);

   CV::translate(0,0);

   bike->render();
}
