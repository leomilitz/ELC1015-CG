#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   this->showCalcs = false;

   background = new Background(screenWidth, screenHeight);
   player = new Player(screenWidth*0.35, screenHeight*0.678, screenWidth*0.32, screenHeight*0.2);
   frames = new Frames();
   speedMultiplier = 1.0;
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   if (keyUp) {
      if (key == 49) toggleCalculations();
      if (key == 200 || key == 202) {
         player->setSpeedMultiplier(1.0);
         background->setSpeedMultiplier(1.0);
      }
   }

   if (!keyUp) {
      if (key == 202) {
         player->setSpeedMultiplier(1.8);
         background->setSpeedMultiplier(2.5);
         return;
      }

      if (key == 200) {
         player->setSpeedMultiplier(0.6);
         background->setSpeedMultiplier(0.5);
         return;
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
