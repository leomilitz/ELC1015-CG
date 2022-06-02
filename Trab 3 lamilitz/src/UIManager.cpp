#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;

   btnSpacingX     = 0.01*screenWidth;
   btnSpacingY     = 0.02*screenHeight;
   btnHeight       = screenHeight*0.0417;
   btnBigWidth     = screenWidth*0.2845;
   btnMedWidth     = (btnBigWidth - btnSpacingX)/2;
   btnSwitch       = (btnBigWidth - 2*btnSpacingX)/3;
   btnSmallWidth   = (btnBigWidth - 3*btnSpacingX)/4;

   background = new Background(screenWidth, screenHeight);
   player = new Player(screenWidth*0.35, screenHeight*0.678, screenWidth*0.32, screenHeight*0.2);

   uiCreate();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;

   for (UIComponent* uiComp : components)
      uiComp->inputManagement(mouseX, mouseY, &mouseState);
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {

}

void UIManager::uiRender() {
   drawBackground();

   for (UIComponent* uiComp : components)
      uiComp->render();
}

void UIManager::drawBackground() {
   CV::clear(1,1,1);
   background->render();
   player->render();
}

void UIManager::uiCreate() {

}
