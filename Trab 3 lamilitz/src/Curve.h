/*
   Curve
   Autor: Leonardo Militz

   Essa classe recebe três pontos e gera uma curva de Bézier.

   ---------------------------------------------------------------------------
   - renderBezier: renderiza uma curva de Bézier.
   - renderBezierFill: renderiza uma curva de Bézier com preenchimento para baixo.
   - sumAll: Adiciona um valor à todos os pontos da curva.
*/

#ifndef CURVE_H
#define CURVE_H

#include "gl_canvas2d.h"
#include <vector>

class Curve {
   public:
      Curve(std::vector<Vector2*> points);

      void renderBezier(float pointSize=1);
      void renderBezierFill(float pointSize=1);
      void sumAll(float value);

      std::vector<Vector2*> points;
};

#endif // CURVE_H
