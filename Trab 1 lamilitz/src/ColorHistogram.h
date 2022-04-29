#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <vector>

#include "gl_canvas2d.h"

class ColorHistogram {
   public:
      ColorHistogram(int x, int y, int sizeX, int sizeY);
      void draw();
      void setColorValues(std::vector<int>& values, char color);
      void setSizeX(int value);
      void setSizeY(int value);
   private:
      int x, y, sizeX, sizeY;
      std::vector<int> redValues, greenValues, blueValues;
};

#endif // COLORHISTOGRAM_H
