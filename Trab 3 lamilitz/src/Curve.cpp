#include "Curve.h"

Curve::Curve(std::vector<Vector2*> points) {
   this->points = points;
}

void Curve::sumAll(float value) {
   for (Vector2* p : points) {
      p->x += value;
   }
}

void Curve::renderBezier(float pointSize) {
   for (float t = 0; t < 1; t += 0.0001) {
      Vector2 p = *points[0]*((1-t)*(1-t)) + *points[1]*((2*t*(1-t))) + *points[2]*(t*t);
      CV::point(p, pointSize);
   }
}

void Curve::renderBezierFill(float pointSize) {
   int lastP = 0;
   for (float t = 0; t < 1; t += 0.0001) {
      Vector2 p = *points[0]*((1-t)*(1-t)) + *points[1]*((2*t*(1-t))) + *points[2]*(t*t);

      if ((int) p.x != lastP)
         CV::line(p, Vector2(p.x,0));

      lastP = p.x;
   }
}
