#include "Slider.h"

Slider::Slider(int startValue, int endValue, int x, int y, int length, int height, std::string caption, std::function<void()> action)
:UIComponent(x, y, x + length, y, caption, action) {
   this->startValue = startValue;
   this->endValue = endValue;
   this->length = length;
   this->currentPosition = 0.5;
   this->btnLength = 12;
   this->btnHeight = 20;
   this->btnPos1 = new Vector2((pos2->x + btnLength)*currentPosition, 0);
   this->btnPos2 = new Vector2(btnPos1->x + btnLength, pos1->y - (height/2));
   this->currentValue = (startValue + endValue)/2;
   this->offset = new Vector2(0,0);
   this->charSize = 10;
   this->isHolding = false;
   this->canGetValue = false;
   this->type = slider;
}

void Slider::updatePosition(int x) {
   btnPos1->x = x;
   btnPos1->y = pos1->y - (btnHeight/2);
   btnPos2->x = btnPos1->x + btnLength;
   btnPos2->y = pos1->y + (btnHeight/2);
   currentValue = startValue + (currentPosition * (abs(startValue) + abs(endValue)));
   currentPosition = (btnPos1->x - pos1->x)/length;
}

void Slider::sliderDrag(Vector2* posMouse) {
   if (isHolding) {
      Vector2 newPos = *posMouse - *offset;

      if (newPos.x <= pos1->x + length && newPos.x >= pos1->x) {
         updatePosition(newPos.x);
         canGetValue = true;

         if (action) action();
      }
   }
}

void Slider::inputManagement(int mouseX, int mouseY, int* mouseState) {
   Vector2* posMouse = new Vector2(mouseX, mouseY);

   if (*btnPos1 <= *posMouse && *btnPos2 >= *posMouse) {
      if (*mouseState == 1) {
         isHolding = false;
      }

      if (*mouseState == 0 && !isHolding) {
         isHolding = true;
         Vector2 _offset = *posMouse - *btnPos1;
         offset->x = _offset.x; offset->y = _offset.y;
      }
   } else if (*mouseState == 1) isHolding = false;

   sliderDrag(posMouse);
}

void Slider::render() {
   canGetValue = false;

   std::string valueStr = std::to_string((int) (currentPosition*100)) + "%";
   int txtSize = valueStr.length();

   CV::color(1,1,1);
   CV::text(pos1->x + 2, pos1->y + 15, caption.c_str());
   CV::text(pos1->x + length - (txtSize*charSize), pos1->y + 15, valueStr.c_str());
   CV::rectFill(pos1->x, pos1->y-1, pos1->x + length, pos1->y+1);

   updatePosition(btnPos1->x);
   CV::color(0.5,0.5,0.5);
   CV::rectFill(*btnPos1, *btnPos2);
   CV::color(0.7,0.7,0.7);
   CV::rectFill(btnPos1->x + 2, pos1->y - (btnHeight/2) + 2, btnPos1->x + btnLength - 2, pos1->y + (btnHeight/2) - 2);
}

int Slider::getValue() {
   return currentValue;
}

void Slider::setValue(int value) {
   currentPosition = (float) (value - startValue)/(abs(startValue) + abs(endValue));
   updatePosition((int) (currentPosition * (pos1->x + length + btnLength)));
}
