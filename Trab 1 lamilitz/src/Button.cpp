#include "Button.h"

Button::Button(Vector2 *v1, Vector2 *v2, std::string text, std::function<void()> action, Color color, bool canToggle) {
   this->v1 = v1;
   this->v2 = v2;
   this->text = text;
   this->edge = new Vector2(2, 2);
   this->action = std::bind(action);
   this->charHalfSize = 5;
   this->btnColor = color;
   this->isToggled = false;
   this->canToggle = canToggle;
}

void Button::drawEdge(float r, float g, float b) {
   CV::color(r, g, b);
   CV::rectFill(*v1 - *edge, *v2 + *edge);
}

void Button::drawHover(){
   float r = 0, g = 0, b = 0;
   float valRgb = 0.9, valGrey = 0.6;

   switch (btnColor) {
      case grey:  r = g = b = valGrey;    break;
      case red:   r = valRgb;             break;
      case green: g = valRgb;             break;
      case blue:  b = valRgb; r=g=0.3;    break;
      case light: r = g = b = 1.0;        break;
   }

   drawEdge(r - 0.2, g - 0.2, b - 0.2);
   CV::color(r, g, b);
}

void Button::drawClick(){
   float r = 0, g = 0, b = 0;
   float valRgb = 0.4, valGrey = 0.3;

   switch (btnColor) {
      case grey:  r = g = b = valGrey;    break;
      case red:   r = valRgb;             break;
      case green: g = valRgb;             break;
      case blue:  b = valRgb; r=g=0.3;    break;
      case light: r = g = b = 0.8;        break;
   }

   drawEdge(r - 0.2, g - 0.2, b - 0.2);
   CV::color(r, g, b);
}

void Button::drawDefault(){
   float r = 0, g = 0, b = 0;
   float valRgb = 0.7, valGrey = 0.5;

   switch (btnColor) {
      case grey:  r = g = b = valGrey;    break;
      case red:   r = valRgb;             break;
      case green: g = valRgb;             break;
      case blue:  b = valRgb;             break;
      case light: r = g = b = 9.0;        break;
   }

   drawEdge(r - 0.2, g - 0.2, b - 0.2);
   CV::color(r, g, b);
}

Button::State Button::checkCollision(float mouseX, float mouseY, int mouseState) {
   Vector2* mousePos = new Vector2(mouseX, mouseY);
   if (*mousePos >= *v1 && *mousePos <= *v2 && mouseState == -2 && !isToggled)
      return hovered;

   if (*mousePos >= *v1 && *mousePos <= *v2 && mouseState == 1)
      return clicked;

   if (isToggled)
      return toggled;

   return standard;
}

void Button::onClick() {
   if (canToggle)
      isToggled = !isToggled;

   if (action)
      action();
}

void Button::draw(State state) {
   switch (state) {
      case standard:    drawDefault();    break;
      case clicked:     drawClick();      break;
      case hovered:     drawHover();      break;
      case toggled:     drawClick();      break;
   }

   int textSize = this->text.length();
   const char* text = this->text.c_str();
   CV::rectFill(*v1, *v2);

   if (btnColor == light)
      CV::color(0,0,0);
   else
      CV::color(1,1,1);

   CV::text((v1->x + v2->x)/2 - textSize*charHalfSize, ((v1->y + v2->y)/2) - charHalfSize + 1, text);
}

std::string Button::getCaption() { return text; };

void Button::setToggled(bool isToggled) {
   if (canToggle)
      this->isToggled = isToggled;
};
