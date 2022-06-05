#ifndef BUILDING_H
#define BUILDING_H

#include "../gl_canvas2d.h"

class Building
{
   public:
      Building(float posX, float posY, float width, float height, float r, float g, float b, float speed);
      void render();
      int getWidth();

      float posX, posY;

   private:
      float width, height;
      float r, g, b, speed;
};

#endif // BUILDING_H
