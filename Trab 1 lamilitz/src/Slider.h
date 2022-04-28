#ifndef SLIDER_H
#define SLIDER_H

#include <functional>

#include "gl_canvas2d.h"

class Slider {
   public:
      Slider(int startValue, int endValue, int x, int y, int length, std::string caption, std::function<void()> action);
      int getValue();
      void draw();
   private:
      int value, startValue, endValue, length,
          x, y, currentPosition;
      bool isHolding;
      std::string caption;
      std::function<void()> action;
};

#endif // SLIDER_H
