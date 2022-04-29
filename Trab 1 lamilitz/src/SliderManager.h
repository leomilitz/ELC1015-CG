#ifndef SLIDERMANAGER_H
#define SLIDERMANAGER_H

#include "Slider.h"

#include <vector>

class SliderManager
{
   public:
      SliderManager();
      void addSlider(int startValue, int endValue, int x, int y, int length, std::string caption, std::function<void()> action);
      void renderSliders();
      void inputManagement(int mouseX, int mouseY, int* mouseState);
      void setSliderState(int brightness, int contrast);
      void resetSliders();
      int getValue();
   private:
      std::vector<Slider*> sliders;
};

#endif // SLIDERMANAGER_H
