#include "ButtonManager.h"

ButtonManager::ButtonManager() {

}

void ButtonManager::addButton(Vector2* p1, Vector2* p2, std::string caption, std::function<void()> action, Button::Color color, bool canToggle) {
   Button* btn = new Button(p1, p2, caption, action, color, canToggle);
   buttons.push_back(btn);
}

void ButtonManager::renderButtons(int mouseX, int mouseY, int mouseState) {
   for (Button* btn : buttons) {
      Button::State state = btn->checkCollision(mouseX, mouseY, mouseState);
      btn->draw(state);
   }
}

void ButtonManager::inputManagement(int mouseX, int mouseY, int* mouseState) {
   for (Button* btn : buttons) {
      Button::State state = btn->checkCollision(mouseX, mouseY, *mouseState);

      if (*mouseState == 1 && state == Button::clicked) {
         btn->onClick();
         *mouseState = -2;
      }
   }
}

void ButtonManager::setButtonState(std::vector<Image::Filter> filters) {
   for (Button* btn : buttons) {
      bool hasRed       = (std::count(filters.begin(), filters.end(), Image::Filter::red) > 0);
      bool hasGreen     = (std::count(filters.begin(), filters.end(), Image::Filter::green) > 0);
      bool hasBlue      = (std::count(filters.begin(), filters.end(), Image::Filter::blue) > 0);
      bool hasLuminance = (std::count(filters.begin(), filters.end(), Image::Filter::luminance) > 0);

      if (btn->getCaption() == "R")
         (hasRed)       ? btn->setToggled(false) : btn->setToggled(true);

      if (btn->getCaption() == "G")
         (hasGreen)     ? btn->setToggled(false) : btn->setToggled(true);

      if (btn->getCaption() == "B")
         (hasBlue)      ? btn->setToggled(false) : btn->setToggled(true);

      if (btn->getCaption() == "L")
         (hasLuminance) ? btn->setToggled(false) : btn->setToggled(true);
   }
}

void ButtonManager::resetButtonState() {
   if (buttons.size() == 0) return;

   for (Button* btn : buttons) {
      btn->setToggled(false);
   }
}
