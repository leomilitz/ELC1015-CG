#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   this->showCalcs = false;

   background = new Background(screenWidth, screenHeight);
   player = new Player(screenWidth*0.35, screenHeight*0.678, screenWidth*0.32, screenHeight*0.2);
   frames = new Frames();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   if (keyUp) {
      //printf("\nkey: %d", key);

      switch (key) {
         case 49:    toggleCalculations();   break;
      }
   }
}

void UIManager::uiRender() {
   float fps = frames->getFrames();
   CV::clear(1,1,1);
   background->render(fps);
   player->render(fps);
   CV::color(1,0,0);
   CV::text(0,0, std::to_string((int)fps).c_str());
}

void UIManager::toggleCalculations() {
   showCalcs = !showCalcs;
   player->showCalculations(showCalcs);
   background->showCalculations(showCalcs);
}
