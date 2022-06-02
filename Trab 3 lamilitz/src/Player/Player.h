#ifndef PLAYER_H
#define PLAYER_H

#include "../gl_canvas2d.h"
#include "Bike.h"

class Player {
   public:
      Player(int width, int height, int posX, int posY);
      void render();

   private:
      int width, height, posX, posY;
      Bike *bike;

};

#endif // PLAYER_H
