#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <algorithm>

#include "Bmp.h"
#include "Vector2.h"
#include "gl_canvas2d.h"

#include <sstream>

typedef struct { int r, g, b; } Pixel;

class Image {
   public:
      enum State  { clicked, hovered, holding, standard };
      enum Filter { red, green, blue, luminance, inverted, bgr };

      Image(std::string &path, int idx, int x, int y);

      void imgRender();
      void resizeImage(double scale);
      void flipHorizontal();
      void flipVertical();
      void rotateImg(int side);
      bool checkCollision(int mouseX, int mouseY);

      bool isCurrentImg();
      State getImgState(int mouseX, int mouseY, int mouseState);
      std::vector<Filter> getActiveFilters();
      int getIndex();
      int getBrightness();
      int getContrast();
      int getWidth();
      int getHeight();
      std::string getImgName();
      std::vector<int> getRGBValues(char color);

      void setIndex(int idx);
      void setImgFront(bool isFront);
      void setCurrent(bool isCurrent);
      void setFilter(Filter filter);
      void setBrightness(int value);
      void setContrast(int value);

   private:
      void imgLoad();
      void imgDrawSelectionOutline();
      void imgDrawHoveringOutline();
      void imgDragAround(Vector2 *posMouse);
      void updatePosition(int x, int y);
      void modelData();
      int  truncateColor(int val);

      Bmp* bmp;
      std::string imgName;
      std::vector<Pixel*> data;
      std::vector<Filter> activeFilters;
      std::vector<int> redValues, greenValues, blueValues, luminanceValues;
      int outline, index, width, height, contrast, brightness;
      float scale;
      bool isHolding, isFront, isCurrent;
      Vector2 *pos1, *pos2, *offset;
      State imgState;
};

#endif // IMAGE_H
