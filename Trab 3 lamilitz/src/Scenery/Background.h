#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <random>
#include "../gl_canvas2d.h"
#include "../Curve.h"
#include "Mountain.h"
class Background
{
   public:
      Background(int screenWidth, int screenHeight);
      void render();

   private:
      void drawGround();
      void drawSky();
      void drawMountains();
      void addMountain();
      void createFirstMountain();
      int getOutOfBoundsMountain();

      int screenWidth, screenHeight;

      std::vector<Mountain*> mountains;
};

#endif // BACKGROUND_H
