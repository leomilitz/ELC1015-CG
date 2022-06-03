#ifndef BIKE_H
#define BIKE_H

#include <vector>
#include <math.h>
#include "Wheel.h"
#include "Pedal.h"

class Bike {
   public:
      Bike(int length, int posX, int posY);
      void render();

   private:
      float wheelRadius, bodyLength, bodyThickness;
      int length, posX, posY;

      Pedal *pedalFront, *pedalBack;
      std::vector<Wheel*> wheels;
};

#endif // BIKE_H
