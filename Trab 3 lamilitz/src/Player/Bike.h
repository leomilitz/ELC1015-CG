/*
   Stickman
   Autor: Leonardo Militz

   Classe que centraliza as partes da bicicleta, como o pedal frontal e dianteiro, as rodas e o corpo.
*/

#ifndef BIKE_H
#define BIKE_H

#include <vector>
#include <math.h>
#include "Wheel.h"
#include "Pedal.h"

class Bike {
   public:
      Bike(int length, int posX, int posY);
      void render(float fps);
      void setSpeedMultiplier(float multiplier);
      Pedal* getPedal(bool isFrontPedal);
      Vector2 getPedalCoords(bool isFrontPedal);

   private:
      float wheelRadius, bodyLength, bodyThickness;
      int length, posX, posY;

      Pedal *pedalFront, *pedalBack;
      std::vector<Wheel*> wheels;
};

#endif // BIKE_H
