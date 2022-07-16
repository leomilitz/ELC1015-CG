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

#include <vector>

#include "gl_canvas2d.h"
#include "Utils/Vector3.h"

class Curve {
   public:
      Curve(std::vector<Vector3*> points);
      Curve();

      void renderBezier(float pointSize=1);
      void setPoints(std::vector<Vector3*> points);
      std::vector<Vector3*> getDiscreteCurve(float discStep);

      std::vector<Vector3*> points;
      float step;
   private:
      double computeBinominal(int n, int k);
};

#endif // CURVE_H
