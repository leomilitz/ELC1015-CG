/*
   Building
   Autor: Leonardo Militz

   Classe responsável por desenhar prédios. Os prédios tem um espaçamento aleatório entre si;
   sua largura, altura e cor também são aleatórias.
   --------------------------------------------------------------------------------------
   - createWindows: Cria as janelas com base na largura e altura do prédio. Existe 40%
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
