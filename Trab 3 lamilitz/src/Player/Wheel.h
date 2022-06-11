#ifndef WHEEL_H
#define WHEEL_H

#include "../gl_canvas2d.h"

class Wheel
{
   public:
      Wheel(int radius, int centerX, int centerY, int tireThickness=10);
      void render(float fps);
      void setSpeedMultiplier(float multiplier);

   private:
      void drawSpokes();
      int radius, centerX, centerY, tireThickness;
      float speed, speedMultiplier, angle, fps;
};

#endif // WHEEL_H
