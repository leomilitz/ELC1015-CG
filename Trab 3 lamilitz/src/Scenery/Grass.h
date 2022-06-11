/*
   Grass
   Autor: Leonardo Militz

   Classe para renderizar uma parcela de grama no cen�rio. Seu tamanho e cor � gerada
   aleat�riamente na classe Background. Existe 20% de chance de spawnar uma grama com
   aparencia de "crescida".
*/

#ifndef GRASS_H
#define GRASS_H

#include "../gl_canvas2d.h"
#include "../RandomUtils.h"

class Grass {
   public:
      Grass(Vector2 pos, float width, float height, float r, float g, float b, float speed, float speedMultiplier);

      void render(float fps);
      void setSpeedMultiplier(float multiplier);
      float getWidth();

      Vector2 pos;
   private:
      float speed, speedMultiplier, width, height, r, g, b;
      bool hasOvergrownGrass;

      RandomUtils ru;
};

#endif // GRASS_H
