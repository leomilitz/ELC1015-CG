#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <random>
#include "../gl_canvas2d.h"
#include "Mountain.h"
#include "Building.h"

class Background
{
   public:
      Background(int screenWidth, int screenHeight);
      void render();

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
      float mountainSpeed, buildingSpeed;

      std::vector<Mountain*> mountains;
      std::vector<Building*> buildings;
      std::random_device rd;
};

#endif // BACKGROUND_H
