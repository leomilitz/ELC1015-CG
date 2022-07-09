#include "Curve.h"

Curve::Curve(std::vector<Vector2*> points) {
   this->points = points;
}

void Curve::sumAll(float value) {
   for (Vector2* p : points) {
      p->x += value;
   }
}

double Curve::computeBinominal(int n, int k) {

    double value = 1.0;

    for (int i = 1; i <= k; i++) {

        value = value * ((n + 1 - i) / i);
    }

    if (n == k) {
        value = 1;
    }

    return value;
}

void Curve::renderBezier(float pointSize) {
   float n = points.size()-1;

   for (float t = 0; t < 1; t += 0.001) {
      float x = 0, y = 0;

      for (int i = 0; i <= n; i++) {
         x += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * points[i]->x;
         y += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * points[i]->y;
      }

      Vector2 p = Vector2(x,y);
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
