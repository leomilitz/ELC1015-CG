#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../gl_canvas2d.h"
#include "../RandomUtils.h"

#include "Mountain.h"
#include "Building.h"
#include "Grass.h"

class Background
{
   public:
      Background(int screenWidth, int screenHeight);
      void render(float fps);
      void showCalculations(bool showCalcs);

   private:
      void drawGround();
      void drawSky();
      void drawMountains();
      void drawBuildings();
      void drawGrass();
      void addMountain();
      void addBuilding();
      void addGrass();
      void createFirstMountain();
      void createFirstBuilding();
      void createFirstGrass();
      int getOutOfBoundsMountain();
      int getOutOfBoundsBuilding();
      int getOutOfBoundsGrass();

      int screenWidth, screenHeight;
      float mountainSpeed, buildingSpeed, grassSpeed, fps;
      bool showCalcs;

      std::vector<Mountain*> mountains;
      std::vector<Building*> buildings;
      std::vector<Grass*>  grass;

      RandomUtils ru;
};

#endif // BACKGROUND_H
