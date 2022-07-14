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
   sweepCurve = new SweepCurve(modelingCurve, screenWidth*0.75, screenHeight*0.5);

   uiCreate();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;

   for (UIComponent* uiComp : components)
      uiComp->inputManagement(mouseX, mouseY, &mouseState);

   sweepCurve->inputManagement(button, &mouseState, wheel, direction, mouseX, mouseY);
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {

}

void UIManager::drawBackground() {
   CV::color(0,0,0);
   CV::rectFill(0, 0, screenWidth*0.48, screenHeight);
   CV::color(1,1,1);
   CV::line(screenWidth*0.48, 0, screenWidth*0.48, screenHeight, screenWidth*0.003);
   CV::line(0, screenHeight - btnHeight*2, screenWidth*0.48, screenHeight - btnHeight*2, screenWidth*0.003);
}

void UIManager::uiRender() {
   float fps = frames->getFrames();
   showFps(fps);

   updateCurveCoordinates();
   sweepCurve->render(fps);
   drawBackground();
   modelingCurve->renderBezier();

   for (UIComponent* uiComp : components)
      uiComp->render();
}

void UIManager::uiCreate() {
   components.push_back(new Button(screenWidth*0.01, screenHeight*0.98 - btnHeight, screenWidth*0.01 + btnMedWidth, screenHeight*0.98,
                                   "Add Node", [this](){ this->addNode(); }));
}

void UIManager::updateCurveCoordinates() {
   std::vector<Vector3*> curve;

   for (UIComponent* uiComp : components) {
      if (uiComp->getType() == UIComponent::node) {
         Node* n = dynamic_cast<Node*>(uiComp);
         Vector2* coord = n->getCoordinates();
         curve.push_back(new Vector3(coord->x, coord->y, 0));
      }
   }

   modelingCurve->setPoints(curve);

   if (curve.size() > 0)
      sweepCurve->setCurve(modelingCurve);
}

void UIManager::addNode() {
   if (nodeCounter <= NODE_MAX) {
      Node* n = new Node(screenWidth*0.25, screenHeight*0.5, nodeRadius);
      n->setLimit(screenWidth*0.48, screenHeight*0.97 - btnHeight*2);
      components.push_back(n);
      nodeCounter++;
   }
}

void UIManager::showFps(float fps) {
   CV::color(1,0,0);
   CV::text(screenWidth*0.49,5, std::to_string((int)fps).c_str());
}
