#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include <string>
#include <functional>
#include <vector>
#include <algorithm>

#include "Vector2.h"
#include "Button.h"

class ButtonManager
{
   public:
      ButtonManager();
      void addButton(Vector2* p1, Vector2* p2, std::string caption, std::function<void()> action,
                     Button::Color color=Button::Color::grey, bool canToggle=false);
      void renderButtons(float mouseX, float mouseY, int mouseState);
      void inputManagement(float mouseX, float mouseY, int* mouseState);

      void setButtonState(std::vector<Image::Filter> filters);
      void resetButtonState();
   private:
      std::vector<Button*> buttons;
};

#endif // BUTTONMANAGER_H
