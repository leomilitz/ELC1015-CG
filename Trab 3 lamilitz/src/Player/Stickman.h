/*
   Stickman
   Autor: Leonardo Militz

   Classe que desenha o tronco (curva de Bézier) do stickman e sua cabeça.
*/

#ifndef STICKMAN_H
#define STICKMAN_H

#include "gl_canvas2d.h"
#include "Curve.h"

class Stickman {
   public:
      Stickman(int posX, int posY, float radius, int bikeX, int bikeY);
      void render(float fps);
      Vector2 getSeatCoords();
      Curve* getBackCoords();

   private:
      int posX, posY, bikeX, bikeY;
      float radius;
      Curve* stkBack;
      std::vector<Vector2*> backCoords;
      Vector2* neck;
};

#endif // STICKMAN_H
