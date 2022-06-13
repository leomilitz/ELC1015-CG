/*
   Wheel
   Autor: Leonardo Militz

   Renderiza uma roda de bicileta com vários raios que ficam girando.
*/

#ifndef WHEEL_H
#define WHEEL_H

#include "../gl_canvas2d.h"

class Wheel {
   public:
      Wheel(int radius, int centerX, int centerY, int tireThickness=10);
      void render(float fps);
      void setSpeedMultiplier(float multiplier);

   private:
      void drawSpokes();
      int radius, centerX, centerY, tireThickness;
      float speed, speedMultiplier, angle;
};

#endif // WHEEL_H
