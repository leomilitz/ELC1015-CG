/*
   Building
   Autor: Leonardo Militz

   Classe respons�vel por desenhar pr�dios. Os pr�dios tem um espa�amento aleat�rio entre si;
   sua largura, altura e cor tamb�m s�o aleat�rias.
   --------------------------------------------------------------------------------------
   - createWindows: Cria as janelas com base na largura e altura do pr�dio. Existe 40%
                  de chance de uma janela aparecer acesa.
*/

#ifndef BUILDING_H
#define BUILDING_H

#include "../gl_canvas2d.h"
#include "../RandomUtils.h"
#include <vector>

class Building {
   public:
      Building(float posX, float posY, float width, float height, float r, float g, float b, float speed, float speedMultiplier);
      void render(float fps);
      void setSpeedMultiplier(float multiplier);
      int getWidth();

      float posX, posY;

   private:
      void drawWindows(float fps);
      void createWindows();

      float width, height, windowWidth, windowHeight, windowSpacing;
      float r, g, b, speed, speedMultiplier;

      std::vector<Vector2*> windows;
      RandomUtils ru;
};

#endif // BUILDING_H
