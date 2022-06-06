#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;

   background = new Background(screenWidth, screenHeight);
   player = new Player(screenWidth*0.35, screenHeight*0.678, screenWidth*0.32, screenHeight*0.2);
   frames = new Frames();

   uiCreate();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {

}

void UIManager::uiRender() {
   float fps = frames->getFrames();
   CV::clear(1,1,1);
   background->render(fps);
   player->render(fps);
}

void UIManager::uiCreate() {

}
