#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   this->showCalcs = false;
   this->speedMultiplier = 1.0;

   float tooltipX = screenWidth*0.03;
   float tooltipY = screenHeight*0.95;
   const char* tooltipText = "Keyboard Controls:\n\n- Left and right arrows to control speed\n- Press \"1\" to view the calculations";
   components.push_back(new Tooltip(tooltipX, tooltipY, 12, tooltipText, screenWidth*0.41, -1, 1, true, "?"));

   background = new Background(screenWidth, screenHeight);
   player = new Player(screenWidth*0.35, screenHeight*0.678, screenWidth*0.32, screenHeight*0.2);
   frames = new Frames();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;

   for (UIComponent* uiComp : components)
      uiComp->inputManagement(mouseX, mouseY, &mouseState);
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   if (keyUp) {
      if (key == 49) toggleCalculations();
      if (key == 200 || key == 202) {
         player->setSpeedMultiplier(1.0);
         background->setSpeedMultiplier(1.0);
      }
   } else {
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
   CV::clear(1,1,1);
   float fps = frames->getFrames();
   background->render(fps);
   player->render(fps);
   CV::color(1,0,0);
   CV::text(0,0, std::to_string((int)fps).c_str());

   for (UIComponent* uiComp : components)
      uiComp->render();
}

void UIManager::toggleCalculations() {
   showCalcs = !showCalcs;
   player->showCalculations(showCalcs);
   background->showCalculations(showCalcs);
}
