#ifndef SLIDER_H
#define SLIDER_H

#include <functional>

#include "gl_canvas2d.h"

class Slider {
   public:
      Slider(int startValue, int endValue, int x, int y, int length, std::string caption, std::function<void()> action);
      int getValue();
      void checkInput(int mouseX, int mouseY, int* mouseState);
      void draw();

      bool canGetValue;
   private:
      enum State { clicked, hovered, standard, holding };
      int value, startValue, endValue, length, charSize, btnLength, btnHeight, currentValue;
      float currentPosition;
      Vector2* startPos, *btnPos1, *btnPos2, *offset;
      State btnState;
      bool isHolding;
      std::string caption;
      std::function<void()> action;
      void sliderDrag(Vector2* posMouse);
      void updatePosition(int x);
};

#endif // SLIDER_H
