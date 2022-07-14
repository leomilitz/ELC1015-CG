#include "Button.h"

Button::Button(int x1, int y1, int x2, int y2, std::string caption, std::function<void()> action, Color color, bool canToggle)
:UIComponent(x1, y1, x2, y2, caption, action) {
   this->edge = new Vector2(2, 2);
   this->btnColor = color;
   this->isToggled = false;
   this->canToggle = canToggle;
   this->state = standard;
   this->type = button;
}

void Button::drawEdge(float r, float g, float b) {
   CV::color(r, g, b);
   CV::rectFill(*pos1 - *edge, *pos2 + *edge);
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

void Button::inputManagement(int mouseX, int mouseY, int* mouseState, int button) {
   Vector2* mousePos = new Vector2(mouseX, mouseY);
   if (*mousePos >= *pos1 && *mousePos <= *pos2 && *mouseState == -2 && !isToggled) {
      state = hovered;
      return;
   }

   if (*mousePos >= *pos1 && *mousePos <= *pos2 && *mouseState == 1) {
      state = clicked;
      onClick();
      return;
   }

   if (isToggled) {
      state = toggled;
      return;
   }

    state = standard;
}

void Button::onClick() {
   if (canToggle)
      isToggled = !isToggled;

   if (action)
      action();
}

void Button::render() {
   switch (state) {
      case standard:    drawDefault();    break;
      case clicked:     drawClick();      break;
      case hovered:     drawHover();      break;
      case toggled:     drawClick();      break;
   }

   int captionSize = this->caption.length();
   const char* caption = this->caption.c_str();
   CV::rectFill(*pos1, *pos2);

   if (btnColor == light)
      CV::color(0,0,0);
   else
      CV::color(1,1,1);

   CV::text((pos1->x + pos2->x)/2 - captionSize*(CHARSIZE/2), ((pos1->y + pos2->y)/2) - (CHARSIZE/2) + 1, caption);
}

void Button::setToggled(bool isToggled) {
   if (canToggle) this->isToggled = isToggled;
}
