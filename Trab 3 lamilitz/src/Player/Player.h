#ifndef PLAYER_H
#define PLAYER_H

#include "../gl_canvas2d.h"
#include "Bike.h"

class Player {
   public:
      Player(int width, int height, int spawnX, int spawnY);
      void render();

   private:
      int width, height, spawnX, spawnY;
      Bike *bike;

};

#endif // PLAYER_H
