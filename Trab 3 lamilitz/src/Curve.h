#ifndef CURVE_H
#define CURVE_H

#include "gl_canvas2d.h"
#include <vector>

class Curve
{
   public:
      Curve(std::vector<Vector2>& points);
      void renderBezier(float pointSize=1);

      std::vector<Vector2> points;
};

#endif // CURVE_H
