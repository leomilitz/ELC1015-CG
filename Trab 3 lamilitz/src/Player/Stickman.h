#ifndef STICKMAN_H
#define STICKMAN_H

#include "gl_canvas2d.h"
#include "Curve.h"

class Stickman
{
   public:
      Stickman(int posX, int posY, float radius, int bikeX, int bikeY);
      void render(float fps);

   private:
      int posX, posY, bikeX, bikeY;
      float radius;
      Curve* stkBack;
      std::vector<Vector2*> backCoords;
      Vector2* neck;
};

#endif // STICKMAN_H
