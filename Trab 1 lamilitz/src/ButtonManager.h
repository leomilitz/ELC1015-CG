#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include "Vector2.h"
#include "Button.h"

class ButtonManager {
   public:
      ButtonManager();

      void addButton(Vector2* p1, Vector2* p2, std::string caption, std::function<void()> action,
                     Button::Color color=Button::Color::grey, bool canToggle=false);
      void renderButtons(int mouseX, int mouseY, int mouseState);
      void inputManagement(int mouseX, int mouseY, int* mouseState);
      void resetButtonState();

      void setButtonState(std::vector<Image::Filter> filters);

   private:
      std::vector<Button*> buttons;
};

#endif // BUTTONMANAGER_H
