#include "Curve.h"

Curve::Curve(std::vector<Vector3*> points) {
   this->points = points;
   this->step = 0.001;
}

Curve::Curve() {
   this->points = std::vector<Vector3*>(0);
   this->step = 0.001;
}

double Curve::computeBinominal(int n, int k) {

    double value = 1.0;

    for (int i = 1; i <= k; i++)
        value = value * ((n + 1 - i) / i);

    if (n == k)
        value = 1;

    return value;
}

void Curve::renderBezier(float pointSize) {
   float n = points.size()-1;

   if (points.size() > 0) {
      for (float t = 0; t < 1; t += step) {
         float x = 0, y = 0;

         for (int i = 0; i <= n; i++) {
            x += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * points[i]->x;
            y += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * points[i]->y;
         }

         Vector2 p = Vector2(x,y);
         CV::point(p, pointSize);
      }
   }
}

std::vector<Vector3*> Curve::getDiscreteCurve(float discStep) {
   std::vector<Vector3*> disc;

   float n = points.size()-1;

   if (points.size() > 0) {
      for (float t = 0; t < 1; t += discStep) {
         float x = 0, y = 0;

         for (int i = 0; i <= n; i++) {
            x += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * points[i]->x;
            y += computeBinominal(n, i) * pow((1 - t), (n - i)) * pow(t, i) * points[i]->y;
         }

         disc.push_back(new Vector3(x,y,1));
      }
   }

   return disc;
}

void Curve::setPoints(std::vector<Vector3*> points) {
   this->points = points;
}
