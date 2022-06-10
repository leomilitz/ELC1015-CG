#ifndef GRASS_H
#define GRASS_H

#include "../gl_canvas2d.h"

class Grass {
   public:
      Grass(Vector2 pos, float width, float height, float r, float g, float b, float grassSpeed);

      void render(float fps);
      float getWidth();

      Vector2 pos;
   private:
      float speed, width, height, r, g, b;
};

#endif // GRASS_H
