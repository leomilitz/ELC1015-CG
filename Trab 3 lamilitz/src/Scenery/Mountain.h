/*
   Mountain
   Autor: Leonardo Militz

   Classe para desenhar uma montanha. A montanha � uma curva de B�zier com tr�s pontos,
   preenchida com linhas at� y = 0 para fazer a pintura. O posicionamento do ponto central
   da montanha � gerado aleat�riamente na classe Background.
*/

#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "../Curve.h"
#include <vector>

class Mountain {
   public:
      Mountain(Curve *curve, float r, float g, float b, float speed, float speedMultiplier);
      void render(float fps);
      void setSpeedMultiplier(float multiplier);

      Curve *curve;
   private:
      float speed, speedMultiplier, r, g, b;
};

#endif // MOUNTAIN_H
