#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;

   btnSpacingX   = screenWidth*0.01;
   btnSpacingY   = screenHeight*0.02;
   btnHeight     = screenHeight*0.0417;
   btnBigWidth   = screenWidth*0.2845;
   nodeRadius    = screenWidth*0.01;
   btnMedWidth   = (btnBigWidth - btnSpacingX)*0.5;
   btnSwitch     = (btnBigWidth - 2*btnSpacingX)/3;
   btnSmallWidth = (btnBigWidth - 3*btnSpacingX)*0.25;

   nodeCounter = 0;
   frames = new Frames();
   modelingCurve = new Curve();

   uiCreate();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;

   for (UIComponent* uiComp : components)
      uiComp->inputManagement(mouseX, mouseY, &mouseState);
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {

}

void UIManager::drawBackground() {
   CV::color(1,1,1);
   CV::line(screenWidth*0.30, 0, screenWidth*0.30, screenHeight, screenWidth*0.003);
   CV::line(0, screenHeight - btnHeight*2, screenWidth*0.30, screenHeight - btnHeight*2, screenWidth*0.003);
}

void UIManager::uiRender() {
   showFps();
   drawBackground();

   for (UIComponent* uiComp : components)
      uiComp->render();

   updateCurveCoordinates();
   modelingCurve->renderBezier();
}

void UIManager::uiCreate() {
   components.push_back(new Button(screenWidth*0.01, screenHeight*0.98 - btnHeight, screenWidth*0.01 + btnMedWidth, screenHeight*0.98,
                                   "Add Node", [this](){ this->addNode(); }));
}

void UIManager::updateCurveCoordinates() {
   std::vector<Vector2*> curve;

   for (UIComponent* uiComp : components) {
      if (uiComp->getType() == UIComponent::node) {
         Node* n = dynamic_cast<Node*>(uiComp);
         curve.push_back(n->getCoordinates());
      }
   }

   modelingCurve->setPoints(curve);
}

void UIManager::addNode() {
   if (nodeCounter <= NODE_MAX) {
      Node* n = new Node(screenWidth*0.15, screenHeight*0.5, nodeRadius);
      n->setLimit(screenWidth*0.3, screenHeight*0.97 - btnHeight*2);
      components.push_back(n);
      nodeCounter++;
   }
}

void UIManager::showFps() {
   float fps = frames->getFrames();
   CV::color(1,0,0);
   CV::text(screenWidth*0.31,5, std::to_string((int)fps).c_str());
}
