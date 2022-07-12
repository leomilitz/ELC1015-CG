#ifndef SWEEPCURVE_H
#define SWEEPCURVE_H

#include <vector>

#include "Curve.h"
#include "Vector3.h"

class SweepCurve
{
   public:
      SweepCurve(Curve* curve, float x, float y);
      virtual ~SweepCurve();

      void render(float fps);
      void setCurve(Curve* curve);

   private:
      std::vector<Vector3*> points;
      Curve* curve;
      int sweepDivisor;
      float fps;
      float posX, posY;
};

#endif // SWEEPCURVE_H
