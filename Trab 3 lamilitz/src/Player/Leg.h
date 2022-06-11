/*
   Leg
   Autor: Leonardo Militz

   Classe que desenha a perna do stickman com base na posi��o do inicio do tronco
   e dos pedais. A posi��o do joelho � calculada utilizando intersec��o de circulos
   de forma que as coxas e as canelas do stickman n�o se deformem.
*/

#ifndef LEG_H
#define LEG_H

#include "Stickman.h"
#include "Pedal.h"
#include "Vector2.h"

class Leg {
   public:
      Leg(Stickman* stickman, Pedal* pedal, float legSize);
      void render(float fps);
      Vector2 getKneePosition();
      float getLegSize();

   private:
      float legSize;
      Stickman* stickman;
      Pedal* pedal;
      Vector2 knee;
};

#endif // LEG_H
