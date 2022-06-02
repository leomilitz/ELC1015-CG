#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../gl_canvas2d.h"

class Background
{
   public:
      Background(int screenWidth, int screenHeight);
      void render();

   private:
      void drawGround();
      void drawSky();

      int screenWidth, screenHeight;
};

#endif // BACKGROUND_H
