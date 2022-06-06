#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdlib.h>
#include <time.h>
#include "../gl_canvas2d.h"
#include "Mountain.h"
#include "Building.h"

class Background
{
   public:
      Background(int screenWidth, int screenHeight);
      void render(float fps);

   private:
      void drawGround();
      void drawSky();
      void drawMountains();
      void drawBuildings();
      void addMountain();
      void createFirstMountain();
      int getOutOfBoundsMountain();
      void addBuilding();
      void createFirstBuilding();
      int getOutOfBoundsBuilding();

      int screenWidth, screenHeight;
      float mountainSpeed, buildingSpeed, fps;

      std::vector<Mountain*> mountains;
      std::vector<Building*> buildings;
};

#endif // BACKGROUND_H
