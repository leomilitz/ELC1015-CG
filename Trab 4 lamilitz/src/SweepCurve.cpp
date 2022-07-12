#include "SweepCurve.h"

SweepCurve::SweepCurve(Curve* curve, float x, float y) {
   this->curve = curve;
   sweepDivisor = 10;
   posX = x;
   posY = y;
}

void SweepCurve::render(float fps) {
   this->fps = fps;

   points = curve->getDiscreteCurve(0.1);

   CV::color(1,1,1);
   for (Vector3* p : points) {
      CV::point(Vector2(posX + p->x, p->y), 3);
   }
}

void SweepCurve::setCurve(Curve* curve) {
   this->curve = curve;
}

SweepCurve::~SweepCurve() {}
