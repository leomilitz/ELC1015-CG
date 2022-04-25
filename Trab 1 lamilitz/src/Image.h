#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "Bmp.h"
#include "Vector2.h"
#include "gl_canvas2d.h"

class Image {
   public:
      enum State { clicked, hovered, holding, standard };

      Image(std::string path, int idx, float x, float y);
      void imgRender();

      Vector2* pos1;
      State imgInputManagement(float mouseX, float mouseY, int mouseState);
      int getIndex();
      void setIndex(int idx);
      bool checkCollision(float mouseX, float mouseY);
      void setImgFront(bool isFront);
      void setCurrent(bool isCurrent);

   private:
      void imgLoad();
      void imgDrawSelectionOutline();
      void imgDrawHoveringOutline();
      void imgDragAround(Vector2* posMouse);
      void updatePosition(float x, float y);

      Bmp* bmp;
      std::string path;
      uchar* imgString;
      int outline, index;
      Vector2* pos2, *offset;
      bool isHolding, isFront, isCurrent;
      State imgState;
};

#endif // IMAGE_H
