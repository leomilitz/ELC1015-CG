#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <algorithm>

#include "Bmp.h"
#include "Vector2.h"
#include "gl_canvas2d.h"

class Image {
   public:
      enum State { clicked, hovered, holding, standard };
      enum Filter { red, green, blue, luminance, inverted, bgr };

      Image(std::string path, int idx, float x, float y);
      void imgRender();

      Vector2* pos1;
      bool checkCollision(float mouseX, float mouseY);

      bool isCurrentImg();
      State getImgState(float mouseX, float mouseY, int mouseState);
      std::vector<Filter> getActiveFilters();
      int getIndex();
      void setIndex(int idx);
      void setImgFront(bool isFront);
      void setCurrent(bool isCurrent);
      void setFilter(Filter filter);
      void setScale(float val);

   private:
      void imgLoad();
      void imgDrawSelectionOutline();
      void imgDrawHoveringOutline();
      void imgDragAround(Vector2* posMouse);
      void updatePosition(float x, float y);
      float truncateColor(float val);

      Bmp* bmp;
      std::string path;
      uchar* imgString;
      int outline, index;
      float scale, brightness, contrast;
      Vector2* pos2, *offset;
      bool isHolding, isFront, isCurrent, isFlippedVert, isFlippedHor;
      State imgState;
      std::vector<Filter> activeFilters;
};

#endif // IMAGE_H
