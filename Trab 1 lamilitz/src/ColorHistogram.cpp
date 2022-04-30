#include "ColorHistogram.h"

ColorHistogram::ColorHistogram(int x, int y, int length, int height) {
   this->x = x;
   this->y = y;
   this->length = length;
   this->height = height;
   this->sizeYScale = ((float) height/(y + height));
   this->sizeXScale = ((float) length/255);
   plotRed = plotGreen = plotBlue = true;
   plotLuminance = false;
}

void ColorHistogram::draw() {
   if (redValues.size() > 0 && blueValues.size() > 0 && greenValues.size() > 0) {
      for (float i = 0; i <= 255; i++) {
         if (plotRed && !plotLuminance) {
            CV::color(1, 0, 0, 0.70);
            CV::line(x + (i*sizeXScale), y, x + (i*sizeXScale), y + redValues[i]*sizeYScale);
         }

         if (plotGreen && !plotLuminance) {
            CV::color(0, 1, 0, 0.70);
            CV::line(x + (i*sizeXScale), y, x + (i*sizeXScale), y + greenValues[i]*sizeYScale);
         }

         if (plotBlue && !plotLuminance) {
            CV::color(0, 0, 1, 0.70);
            CV::line(x + (i*sizeXScale), y, x + (i*sizeXScale), y + blueValues[i]*sizeYScale);
         }

         if (plotLuminance) {
            CV::color(1, 1, 1);
            CV::line(x + (i*sizeXScale), y, x + (i*sizeXScale), y + luminanceValues[i]*sizeYScale);
         }
      }
   }

   CV::color(1,1,1);
   CV::line(x-1, y-1, x+length+3, y-1);
   CV::line(x-1, y-1, x-1, y+height+1);
   CV::line(x+length+3, y-1, x+length+3, y+height+1);
   CV::line(x-1, y+height+1, x+length+3, y+height+1);
}

void ColorHistogram::setActiveChannels(bool r, bool g, bool b, bool l) {
   plotRed = r; plotGreen = g; plotBlue = b; plotLuminance = l;
}

void ColorHistogram::setColorValues(std::vector<int> &values, char color) {
   switch (color) {
      case 'r':   redValues   = values;      break;
      case 'g':   greenValues = values;      break;
      case 'b':   blueValues  = values;      break;
      case 'l':   luminanceValues = values;  break;
   }
}

void ColorHistogram::clearHistogram() {
   redValues.clear();
   greenValues.clear();
   blueValues.clear();
}

void ColorHistogram::setSizeYScale(int highestValue) {
   sizeYScale = ((float) height / highestValue);
}
