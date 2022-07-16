/**
 *  Curve
 *  Autor: Leonardo Militz
 *
 *  Essa classe recebe um vetor de N pontos e gera uma curva de Bézier.
 *
 *  ---------------------------------------------------------------------------
 *  - renderBezier: renderiza uma curva de Bézier com N pontos de controle.
 *  - computeBinomial: Faz o cálculo dos coeficientes binomiais dos polinômios de
 *    Bernstein.
 *  - getDiscreteCurve: Retorna uma amostragem dos pontos da curva com um aumento
 *    do passo (step) usado para gerar a curva.
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
      ~Curve();

      void renderBezier(float pointSize=1);
      void setPoints(std::vector<Vector3*> points);
      std::vector<Vector3*> getDiscreteCurve(float discStep);

      std::vector<Vector3*> points;
   private:
      float step; // Incremento na curva.
      double computeBinominal(int n, int k);
};

#endif // CURVE_H
