/*
   Leg
   Autor: Leonardo Militz

   Classe que desenha a perna do stickman com base na posição do inicio do tronco
   e dos pedais. A posição do joelho é calculada utilizando intersecção de circulos
   de forma que as coxas e as canelas do stickman não se deformem.
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
