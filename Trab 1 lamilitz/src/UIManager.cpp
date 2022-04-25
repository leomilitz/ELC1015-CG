#include "UIManager.h"

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseButton    = button;
   mouseState     = state;
   mouseWheel     = wheel;
   mouseDirection = direction;
   mouseX         = x;
   mouseY         = y;

   btnManager->inputManagement(x, y, &state);
   imgEditor->inputManagement(x, y, state);
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   this->key = key;
   this->keyUp = keyUp;
}

void UIManager::uiRender() {
   btnManager->renderButtons(mouseX, mouseY, mouseState);
   imgEditor->renderImages();
}

void UIManager::uiCreate() {
   float btnOffsetX = 0.01*screenWidth, btnOffsetY = 0.02*screenHeight,
         btnHeight = 25, btnWidth = screenWidth*0.2,
         smallBtnWidth = (btnWidth - 2*btnOffsetX)/3;

   btnManager = new ButtonManager();
   imgEditor  = new ImageEditor();

   // Botões
   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - (btnHeight + btnOffsetY)),
                         new Vector2(btnWidth, screenHeight - btnOffsetY), "Open Image",
                         [this]() { imgEditor->addImage(this->screenWidth*0.7, 0); });

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 2*(btnHeight + btnOffsetY)),
                         new Vector2(btnWidth, screenHeight - (btnHeight + 2*btnOffsetY)), "Reset Image",
                         [this]() { printf("\nnormal filter"); });

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 3*(btnHeight + btnOffsetY)),
                         new Vector2(smallBtnWidth, screenHeight - (2*btnHeight + 3*btnOffsetY)), "R",
                         [this]() { printf("\nRed Filter"); });

   btnManager->addButton(new Vector2(btnOffsetX + smallBtnWidth, screenHeight - 3*(btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + 2*smallBtnWidth, screenHeight - (2*btnHeight + 3*btnOffsetY)), "G",
                         [this]() { printf("\nGreen Filter"); });

   btnManager->addButton(new Vector2(2*btnOffsetX + 2*smallBtnWidth, screenHeight - 3*(btnHeight + btnOffsetY)),
                         new Vector2(2*btnOffsetX + 3*smallBtnWidth, screenHeight - (2*btnHeight + 3*btnOffsetY)), "B",
                         [this]() { printf("\nBlue Filter"); });
}

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   uiCreate();
}
