#include "SweepCurve.h"

SweepCurve::SweepCurve(Curve* curve, float x, float y) {
   this->curve = curve;
   sweepDivisor = 10;
   posX = x;
   posY = y;
}

void SweepCurve::render(float fps) {
   this->fps = fps;

   this->points = curve->getDiscreteCurve(0.1);
}

SweepCurve::~SweepCurve() {}
