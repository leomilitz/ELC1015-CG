#include "Curve.h"

Curve::Curve(std::vector<Vector2>& points) {
   this->points = points;
}

void Curve::renderBezier(float pointSize) {
   for (float t = 0; t < 1; t += 0.0001) {
      Vector2 p = points[0]*((1-t)*(1-t)) + points[1]*((2*t*(1-t))) + points[2]*(t*t);
      CV::color(0,0,0);
      CV::point(p, pointSize);
   }
}
