#ifndef BIKE_H
#define BIKE_H

#include <vector>
#include <math.h>
#include "Wheel.h"

class Bike {
   public:
      Bike(int length, int spawnX, int spawnY);
      void render();

   private:
      float wheelRadius, bodyLength, bodyThickness;
      int length, spawnX, spawnY;

      std::vector<Wheel*> wheels;
};

#endif // BIKE_H
