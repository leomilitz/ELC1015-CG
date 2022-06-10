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
      Vector2 getKneePosition();
      float getLegSize();

   private:
      Stickman* stickman;
      Pedal* pedal;
      float legSize;
      Vector2 knee;
};

#endif // LEG_H
