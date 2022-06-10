#ifndef BUILDING_H
#define BUILDING_H

#include "../gl_canvas2d.h"
#include "../RandomUtils.h"
#include <vector>

class Building
{
   public:
      Building(float posX, float posY, float width, float height, float r, float g, float b, float speed);
      void render(float fps);
      int getWidth();

      float posX, posY;

   private:
      void drawWindows(float fps);
      void createWindows();

      float width, height, windowWidth, windowHeight, windowSpacing;
      float r, g, b, speed;

      std::vector<Vector2*> windows;
      RandomUtils ru;
};

#endif // BUILDING_H
