#ifndef SWEEPCURVE_H
#define SWEEPCURVE_H

#include <vector>

#include "Curve.h"
#include "Vector3.h"

class SweepCurve
{
   public:
      SweepCurve(Curve* curve);
      virtual ~SweepCurve();

   private:
      std::vector<Vector3*> points;
      Curve* curve;
      float pointDivisor;
      int sweepDivisor;
};

#endif // SWEEPCURVE_H
