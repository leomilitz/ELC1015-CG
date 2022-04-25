#include "UIManager.h"

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseButton    = button;
   mouseState     = state;
   mouseWheel     = wheel;
   mouseDirection = direction;
   mouseX         = x;
   mouseY         = y;

   for (Image* image : imgEditor->images) {
      if (image != NULL) {
         Image::State st = image->imgInputManagement(x, y, state);

         if (mouseState == 1 && st == Image::clicked) {
            int idx = imgEditor->checkClickedImagesPriority(x, y);
            imgEditor->setCurrentImage(idx);
            mouseState = -2;
         }
      }
   }
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   this->key = key;
   this->keyUp = keyUp;
}

void UIManager::uiRender() {
   for (Button* btn : buttons) {
      Button::State state = btn->checkCollision(mouseX, mouseY, mouseState);
      btn->draw(state);

      if (mouseState == 1 && state == Button::clicked) {
         btn->onClick();
         mouseState = -2;
      }
   }

   for (Image* image : imgEditor->images) {
      if (image != NULL)
         image->imgRender();
   }
}

void UIManager::uiCreate() {
   int btnOffsetX = 0.01*screenWidth,
       btnOffsetY = 0.02*screenHeight,
       btnHeight = 25;

   imgEditor = new ImageEditor();
   buttons.push_back(new Button(new Vector2(btnOffsetX, screenHeight - (btnHeight + btnOffsetY)),
                                new Vector2(screenWidth*0.2, screenHeight - btnOffsetY), "Abrir Imagem",
                                [this]() { imgEditor->addImage(this->screenWidth*0.7, 0); }));
}

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   uiCreate();
}
