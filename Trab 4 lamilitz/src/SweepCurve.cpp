#include "SweepCurve.h"

SweepCurve::SweepCurve(Curve* curve) {
   this->curve = curve;
   pointDivisor = 10;
   sweepDivisor = 5;
}

SweepCurve::~SweepCurve() {}
