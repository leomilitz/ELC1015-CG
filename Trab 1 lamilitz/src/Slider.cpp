#include "Slider.h"

Slider::Slider(int startValue, int endValue, int x, int y, int length, std::string caption, std::function<void()> action) {
   this->startValue = startValue;
   this->endValue = endValue;
   this->x = x;
   this->y = y;
   this->length = length;
   this->caption = caption;
}

void Slider::draw() {
   CV::color(1,1,1);
   CV::text(x + 2, y + 15, caption.c_str());
   CV::line(x, y,   x + length, y);
   CV::line(x, y-1, x + length, y-1);
}
