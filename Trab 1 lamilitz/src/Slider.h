#ifndef SLIDER_H
#define SLIDER_H

#include <functional>

#include "gl_canvas2d.h"

class Slider {
   public:
      Slider(int startValue, int endValue, int x, int y, int length, std::string &caption, std::function<void()> &action);

      void draw();
      void checkInput(int mouseX, int mouseY, int *mouseState);

      void setValue(int value);
      int getValue();

      bool canGetValue;
      std::string caption;

   private:
      void sliderDrag(Vector2 *posMouse);
      void updatePosition(int x);

      enum State { clicked, hovered, standard, holding };

      int value, startValue, endValue, length, charSize, btnLength, btnHeight, currentValue;
      float currentPosition;
      bool isHolding;
      Vector2 *startPos, *btnPos1, *btnPos2, *offset;
      State btnState;
      std::function<void()> action;
};

#endif // SLIDER_H
