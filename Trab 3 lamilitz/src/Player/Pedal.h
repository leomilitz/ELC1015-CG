#ifndef PEDAL_H
#define PEDAL_H

#include "../gl_canvas2d.h"

class Pedal {
   public:
      Pedal(int centerX, int centerY, float armLength, int orientation);
      void render();

   private:
      void spinPedals();

      float armLength, centerX, centerY, pedalX, pedalY, speed, angle;
};

#endif // PEDAL_H
