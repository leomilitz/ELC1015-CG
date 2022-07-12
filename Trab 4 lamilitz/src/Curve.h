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
#include "Vector2.h"
#include <vector>

class Curve {
   public:
      Curve(std::vector<Vector2*> points);
      Curve();

      void renderBezier(float pointSize=1);
      void setPoints(std::vector<Vector2*> points);

      std::vector<Vector2*> points;
   private:
      double computeBinominal(int n, int k);
};

#endif // CURVE_H
