#ifndef LEG_H
#define LEG_H

#include "Stickman.h"
#include "Pedal.h"
#include "Vector2.h"

class Leg
{
   public:
      Leg(Stickman* stickman, Pedal* pedal, float legSize);
      void render(float fps);

   private:
      Stickman* stickman;
      Pedal* pedal;
      float legSize, pedalSpeed;
};

#endif // LEG_H
