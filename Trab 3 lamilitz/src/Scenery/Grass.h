#ifndef GRASS_H
#define GRASS_H

#include "../gl_canvas2d.h"

class Grass {
   public:
      Grass(Vector2 pos, float width, float height, float r, float g, float b, float speed, float speedMultiplier);

      void render(float fps);
      void setSpeedMultiplier(float multiplier);
      float getWidth();

      Vector2 pos;
   private:
      float speed, speedMultiplier, width, height, r, g, b;
};

#endif // GRASS_H
