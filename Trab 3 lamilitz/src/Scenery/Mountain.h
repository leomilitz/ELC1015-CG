#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "../Curve.h"
#include <vector>

class Mountain
{
   public:
      Mountain(Curve *curve, float r, float g, float b, float speed);
      void render();

      Curve *curve;
   private:
      float speed, r, g, b;
};

#endif // MOUNTAIN_H
