#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <algorithm>

#include "Bmp.h"
#include "Vector2.h"
#include "gl_canvas2d.h"

#include <sstream>

class Image {
   public:
      enum State { clicked, hovered, holding, standard };
      enum Filter { red, green, blue, luminance, inverted, bgr };

      Image(std::string path, int idx, int x, int y);
      void imgRender();
      void resizeImage(double scale);

      bool checkCollision(int mouseX, int mouseY);
      bool isCurrentImg();
      State getImgState(int mouseX, int mouseY, int mouseState);
      std::vector<Filter> getActiveFilters();
      int getIndex();

      void setIndex(int idx);
      void setImgFront(bool isFront);
      void setCurrent(bool isCurrent);
      void setFilter(Filter filter);
      void setBrightness(int value);
      void setContrast(int value);
      void flipHorizontal();
      void flipVertical();
      void rotateImg(int side);

   private:
      typedef struct { int r, g, b; } Pixel;

      void imgLoad();
      void imgDrawSelectionOutline();
      void imgDrawHoveringOutline();
      void imgDragAround(Vector2* posMouse);
      void updatePosition(int x, int y);
      int truncateColor(int val);
      void modelData();

      Bmp* bmp;
      std::string imgPath, imgName;
      std::vector<Pixel*> data;
      int outline, index, width, height, contrast, brightness;
      float scale;
      Vector2* pos1, *pos2, *offset;
      bool isHolding, isFront, isCurrent;
      State imgState;
      std::vector<Filter> activeFilters;
};

#endif // IMAGE_H
