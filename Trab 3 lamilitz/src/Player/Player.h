#ifndef PLAYER_H
#define PLAYER_H

#include "../gl_canvas2d.h"
#include "Leg.h"
#include "Bike.h"
#include "../Curve.h"

class Player {
   public:
      Player(int width, int height, int posX, int posY);
      void render(float fps);
      void showCalculations(bool showCalcs);
      void setSpeedMultiplier(float multiplier);

   private:
      int width, height, posX, posY;
      Bike *bike;
      Stickman *stickman;
      Leg *frontLeg, *backLeg;
      bool showCalcs;
};

#endif // PLAYER_H
