#include "Slider.h"

Slider::Slider(int startValue, int endValue, int x, int y, int length, std::string caption, std::function<void()> action) {
   this->startValue = startValue;
   this->endValue = endValue;
   this->length = length;
   this->caption = caption;
   this->currentPosition = 0.5;
   this->action = std::bind(action);
   this->startPos = new Vector2(x, y);
   this->btnLength = 12;
   this->btnHeight = 20;
   this->btnPos1 = new Vector2((startPos->x + length + btnLength)*currentPosition, 0);
   this->btnPos2 = new Vector2(btnPos1->x + btnLength, startPos->y - (btnHeight/2));
   this->currentValue = (startValue + endValue)/2;
   this->offset = new Vector2(0,0);
   this->charSize = 10;
   this->isHolding = false;
   this->canGetValue = false;
}

void Slider::updatePosition(int x) {
   btnPos1->x = x;
   btnPos1->y = startPos->y - (btnHeight/2);
   btnPos2->x = btnPos1->x + btnLength;
   btnPos2->y = startPos->y + (btnHeight/2);
   currentValue = startValue + (currentPosition * (abs(startValue) + abs(endValue)));
   currentPosition = (btnPos1->x - startPos->x)/length;
}

void Slider::sliderDrag(Vector2* posMouse) {
   if (isHolding) {
      Vector2 newPos = *posMouse - *offset;

      if (newPos.x <= startPos->x + length && newPos.x >= startPos->x) {
         updatePosition(newPos.x);
         canGetValue = true;

         if (action) {
            action();
         }
      }
   }
}

void Slider::checkInput(int mouseX, int mouseY, int* mouseState) {
   Vector2* posMouse = new Vector2(mouseX, mouseY);

   if (*btnPos1 <= *posMouse && *btnPos2 >= *posMouse) {
      if (*mouseState == 1) {
         isHolding = false;
         btnState = clicked;
      }

      if (*mouseState == 0 && !isHolding) {
         isHolding = true;
         Vector2 _offset = *posMouse - *btnPos1;
         offset->x = _offset.x; offset->y = _offset.y;
         btnState = holding;
      }
   } else if (*mouseState == 1) isHolding = false;

   sliderDrag(posMouse);
}

int Slider::getValue() {
   return currentValue;
}

void Slider::setValue(int value) {
   currentPosition = (float) (value - startValue)/(abs(startValue) + abs(endValue));
   updatePosition((int) (currentPosition * (startPos->x + length + btnLength)));
}

void Slider::draw() {
   canGetValue = false;

   std::string valueStr = std::to_string((int) (currentPosition*100)) + "%";
   int txtSize = valueStr.length();
   // barra
   CV::color(1,1,1);
   CV::text(startPos->x + 2, startPos->y + 15, caption.c_str());
   CV::text(startPos->x + length - (txtSize*charSize), startPos->y + 15, valueStr.c_str());
   CV::rectFill(startPos->x, startPos->y-1, startPos->x + length, startPos->y+1);

   // botão
   updatePosition(btnPos1->x);
   CV::color(0.5,0.5,0.5);
   CV::rectFill(*btnPos1, *btnPos2);
   CV::color(0.7,0.7,0.7);
   CV::rectFill(btnPos1->x + 2, startPos->y - (btnHeight/2) + 2, btnPos1->x + btnLength - 2, startPos->y + (btnHeight/2) - 2);
}
