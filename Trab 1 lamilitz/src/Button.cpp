#include "Button.h"

Button::Button(Vector2 *v1, Vector2 *v2, std::string text, std::function<void()> action) {
   this->v1 = v1;
   this->v2 = v2;
   this->text = text;
   this->edge = new Vector2(2, 2);
   this->action = std::bind(action);
   this->charHalfSize = 5;
}

void Button::drawEdge(float r, float g, float b) {
   CV::color(r, g, b);
   CV::rectFill(*v1 - *edge, *v2 + *edge);
}

void Button::drawHover(){
   drawEdge(0.4, 0.4, 0.4);
   CV::color(0.6, 0.6, 0.6);
}

void Button::drawClick(){
   drawEdge(0.2, 0.2, 0.2);
   CV::color(0.4, 0.4, 0.4);
}

void Button::drawDefault(){
   drawEdge(0.3, 0.3, 0.3);
   CV::color(0.5, 0.5, 0.5);
}

Button::State Button::checkCollision(float mouseX, float mouseY, int mouseState) {
   Vector2* mousePos = new Vector2(mouseX, mouseY);
   if (*mousePos >= *v1 && *mousePos <= *v2 && mouseState == -2)
      return hovered;

   if (*mousePos >= *v1 && *mousePos <= *v2 && mouseState == 1)
      return clicked;

   return standard;
}

void Button::onClick() {
   if (action)
      action();
}

void Button::draw(State state) {
   switch (state) {
      case standard:    drawDefault();    break;
      case clicked:     drawClick();      break;
      case hovered:     drawHover();      break;
   }

   int textSize = this->text.length();
   const char* text = this->text.c_str();
   CV::rectFill(*v1, *v2);
   CV::color(1,1,1);
   CV::text((v1->x + v2->x)/2 - textSize*charHalfSize, ((v1->y + v2->y)/2) - charHalfSize + 1, text);
}
