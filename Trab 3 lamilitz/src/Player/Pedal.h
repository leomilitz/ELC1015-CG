#ifndef PEDAL_H
#define PEDAL_H

#include "../gl_canvas2d.h"

class Pedal {
   public:
      Pedal(int centerX, int centerY, float armLength, int orientation);
      void render(float fps);
      void setSpeedMultiplier(float multiplier);
      Vector2 getPedalCoords();
      float getSpeed();
      float getLength();

   private:
      float armLength, centerX, centerY, pedalX, pedalY, speed, angle, speedMultiplier;
};

#endif // PEDAL_H
