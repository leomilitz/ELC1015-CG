#include "ButtonManager.h"

ButtonManager::ButtonManager() {

}

void ButtonManager::addButton(Vector2* p1, Vector2* p2, std::string caption, std::function<void()> action) {
   Button* btn = new Button(p1, p2, caption, action);
   buttons.push_back(btn);
}

void ButtonManager::renderButtons(float mouseX, float mouseY, int mouseState) {
   for (Button* btn : buttons) {
      Button::State state = btn->checkCollision(mouseX, mouseY, mouseState);
      btn->draw(state);
   }
}

void ButtonManager::inputManagement(float mouseX, float mouseY, int* mouseState) {
   for (Button* btn : buttons) {
      Button::State state = btn->checkCollision(mouseX, mouseY, *mouseState);

      if (*mouseState == 1 && state == Button::clicked) {
         btn->onClick();
         *mouseState = -2;
      }
   }
}
