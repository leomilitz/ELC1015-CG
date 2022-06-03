#ifndef STICKMAN_H
#define STICKMAN_H

#include "gl_canvas2d.h"
#include "Curve.h"

class Stickman
{
   public:
      Stickman(int posX, int posY, float radius, int bikeX, int bikeY);
      void render();

   private:
      int posX, posY;
      float radius;
      Curve* stkBack;
      std::vector<Vector2> backCoords;
};

#endif // STICKMAN_H
