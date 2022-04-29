#include "ColorHistogram.h"

ColorHistogram::ColorHistogram(int x, int y, int sizeX, int sizeY) {
   this->x = x;
   this->y = y;
   this->sizeX = sizeX;
   this->sizeY = sizeY;
}

void ColorHistogram::draw() {
   CV::color(1,1,1);
   CV::line(x, y, x + sizeX, y);
   CV::line(x, y, x, y + sizeY);

   if (redValues.size() > 0 && blueValues.size() > 0 && greenValues.size() > 0) {
      for (int i = 0; i < sizeX; i++) {
         // Red
         CV::color(1, 0, 0, 0.5);
         CV::line(x + 1 + i, y + 1, x + i, y + 1 + redValues[i]);
         // Green
         CV::color(0, 1, 0, 0.5);
         CV::line(x + 1 + i, y + 1, x + 1 + i, y + 1 + greenValues[i]);
         // Blue
         CV::color(0, 0, 1, 0.5);
         CV::line(x + 1 + i, y, x + 1 + i, y + 1 + blueValues[i]);
      }
   }
}

void ColorHistogram::setColorValues(std::vector<int>& values, char color) {
   switch (color) {
      case 'r':   redValues   = values;   break;
      case 'g':   greenValues = values;   break;
      case 'b':   blueValues  = values;   break;
   }
}

void ColorHistogram::setSizeX(int value) { sizeX = value; }
void ColorHistogram::setSizeY(int value) { sizeY = value; }
