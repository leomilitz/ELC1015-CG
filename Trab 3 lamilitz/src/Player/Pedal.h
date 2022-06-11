/*
   Pedal
   Autor: Leonardo Militz

   Classe que desenha o pedal da bicicleta que fica rotacionando constantemente.
   Dependendo da orientação (1 ou -1) enviada no construtor, o pedal iniciará
   sendo desenhado para baixo ou para cima.
*/

#ifndef PEDAL_H
#define PEDAL_H

#include "../gl_canvas2d.h"

class Pedal {
   public:
      Pedal(int centerX, int centerY, float armLength, int orientation);
      void render(float fps);
      void setSpeedMultiplier(float multiplier);
      Vector2 getPedalCoords();
      float getLength();

   private:
      float armLength, centerX, centerY, pedalX, pedalY, speed, angle, speedMultiplier;
};

#endif // PEDAL_H
