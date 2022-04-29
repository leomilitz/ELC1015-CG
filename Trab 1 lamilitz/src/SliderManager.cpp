#include "SliderManager.h"

SliderManager::SliderManager() {}

void SliderManager::addSlider(int startValue, int endValue, int x, int y, int length, std::string caption, std::function<void()> action) {
   sliders.push_back(new Slider(startValue, endValue, x, y, length, caption, action));
}

void SliderManager::renderSliders() {
   if (sliders.size() == 0) return;

   for (Slider* slider : sliders)
         slider->draw();
}

void SliderManager::inputManagement(int mouseX, int mouseY, int* mouseState) {
   if (sliders.size() == 0) return;

   for (Slider* slider : sliders) {
      slider->checkInput(mouseX, mouseY, mouseState);
   }
}

int SliderManager::getValue() {
   for (Slider* slider : sliders) {
      if (slider->canGetValue)
         return slider->getValue();
   }
}
