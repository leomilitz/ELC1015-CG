#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;

   btnSpacingX   = screenWidth*0.02;
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
   sweepCurve = new SweepCurve(modelingCurve, screenWidth*0.75, screenHeight*0.5, screenWidth, nodeRadius);
   projMode       = "Perspective";
   faceCount      = "30";
   pointCount     = "11";
   rotationMode   = "Translate Axis";
   yTranslation   = "0";
   sweepLapCount  = "1";

   uiCreate();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   mouseX = x; mouseY = y; mouseState = state;

   for (UIComponent* uiComp : components)
      uiComp->mouseInputManagement(mouseX, mouseY, &mouseState, button);

   sweepCurve->mouseInputManagement(button, &mouseState, wheel, direction, mouseX, mouseY, screenWidth*0.5);
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   for (UIComponent* uiComp : components)
      uiComp->keyboardInputManagement(key, keyUp);

   if ((key == 127 || key == 100) && keyUp)
      removeNode();
}

void UIManager::drawBackground() {
   CV::color(0,0,0);
   CV::rectFill(0, 0, screenWidth*0.48, screenHeight);
   CV::color(1,1,1);
   CV::line(screenWidth*0.48, 0, screenWidth*0.48, screenHeight, screenWidth*0.003);
   CV::line(0, screenHeight - btnHeight*3 - 4*btnSpacingY, screenWidth*0.48, screenHeight - btnHeight*3 - 4*btnSpacingY, screenWidth*0.003);

   CV::text(screenWidth*0.5, screenHeight - btnHeight,     ("Projection:    " + projMode).c_str());
   CV::text(screenWidth*0.5, screenHeight - btnHeight*1.6, ("Rotation Mode: " + rotationMode).c_str());
   CV::text(screenWidth*0.5, screenHeight - btnHeight*2.2, ("Faces:         " + faceCount).c_str());
   CV::text(screenWidth*0.5, screenHeight - btnHeight*2.8, ("Y Translation: " + yTranslation).c_str());
   CV::text(screenWidth*0.5, screenHeight - btnHeight*3.4, ("Points:        " + pointCount).c_str());
   CV::text(screenWidth*0.5, screenHeight - btnHeight*4.0, ("Sweep Laps:    " + sweepLapCount).c_str());
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
   components.push_back(new Button(btnSpacingX, screenHeight - btnHeight - btnSpacingY,
                                   btnSpacingX + btnBigWidth, screenHeight - btnSpacingY,
                                   "Projection Type", [this](){ projMode = this->sweepCurve->changePerspective(); }));

   components.push_back(new Button(3*btnSpacingX + btnMedWidth*2, screenHeight - btnHeight - btnSpacingY,
                                   btnSpacingX*3 + btnMedWidth*2 + btnSmallWidth, screenHeight - btnSpacingY,
                                   "+Face", [this](){ faceCount = this->sweepCurve->addSweepDivisor(1); }));

   components.push_back(new Button(4*btnSpacingX + btnMedWidth*2 + btnSmallWidth, screenHeight - btnHeight - btnSpacingY,
                                   btnSpacingX*4 + btnMedWidth*2 + btnSmallWidth*2, screenHeight - btnSpacingY,
                                   "-Face", [this](){ faceCount = this->sweepCurve->addSweepDivisor(-1); }));

   components.push_back(new Button(btnSpacingX, screenHeight - 2*btnHeight - 2*btnSpacingY,
                                   btnSpacingX + btnBigWidth, screenHeight - 2*btnSpacingY - btnHeight,
                                   "Rotation Mode", [this](){ rotationMode = this->sweepCurve->changeRotationMode(); }));

   components.push_back(new Button(3*btnSpacingX + btnMedWidth*2, screenHeight - 2*btnHeight - 2*btnSpacingY,
                                   btnSpacingX*3 + btnMedWidth*2 + btnSmallWidth, screenHeight - 2*btnSpacingY - btnHeight,
                                   "+Pnt", [this](){ pointCount = this->sweepCurve->addPoints(-0.033); }));

   components.push_back(new Button(4*btnSpacingX + btnMedWidth*2 + btnSmallWidth, screenHeight - 2*btnHeight - 2*btnSpacingY,
                                   btnSpacingX*4 + btnMedWidth*2 + btnSmallWidth*2, screenHeight - 2*btnSpacingY - btnHeight,
                                   "-Pnt", [this](){ pointCount = this->sweepCurve->addPoints(0.033); }));

   components.push_back(new Button(btnSpacingX, screenHeight - btnHeight*3 - btnSpacingY*3,
                                   btnSpacingX + btnMedWidth, screenHeight - btnHeight*2 - btnSpacingY*3,
                                   "Add Node", [this](){ this->addNode(); }));

   components.push_back(new Button(btnSpacingX*2 + btnMedWidth, screenHeight - btnHeight*3 - btnSpacingY*3,
                                   btnSpacingX*2 + btnMedWidth + btnSmallWidth, screenHeight - btnHeight*2 - btnSpacingY*3,
                                   "+Laps", [this]() { sweepLapCount = this->sweepCurve->addSweepLaps(1); }));

   components.push_back(new Button(btnSpacingX*3 + btnMedWidth + btnSmallWidth, screenHeight - btnHeight*3 - btnSpacingY*3,
                                   btnSpacingX*3 + btnMedWidth + btnSmallWidth*2, screenHeight - btnHeight*2 - btnSpacingY*3,
                                   "-Laps", [this]() { sweepLapCount = this->sweepCurve->addSweepLaps(-1); }));

   components.push_back(new Button(3*btnSpacingX + btnMedWidth*2, screenHeight - btnHeight*3 - btnSpacingY*3,
                                   btnSpacingX*3 + btnMedWidth*2 + btnSmallWidth, screenHeight - btnHeight*2 - btnSpacingY*3,
                                   "+TY", [this](){ yTranslation = this->sweepCurve->translateY(1); }));

   components.push_back(new Button(4*btnSpacingX + btnMedWidth*2 + btnSmallWidth, screenHeight - btnHeight*3 - btnSpacingY*3,
                                   btnSpacingX*4 + btnMedWidth*2 + btnSmallWidth*2, screenHeight - btnHeight*2 - btnSpacingY*3,
                                   "-TY", [this](){ yTranslation = this->sweepCurve->translateY(-1); }));


   std::string tooltipText = "Mouse controls:\n- Hold left click to move nodes\nor rotate the 3D figure.\n";
   tooltipText += "\n-------------------------------\n";
   tooltipText += "\nKeyboard Controls:\n- Hover on a node with your\nmouse and press D or DEL\nto delete it.";
   components.push_back(new Tooltip(screenWidth*0.98, screenHeight*0.97, 12, tooltipText, screenWidth*0.32, -1, -1, true, "?"));
}

void UIManager::updateCurveCoordinates() {
   std::vector<Vector3*> curve;

   for (UIComponent* uiComp : components) {
      if (uiComp->getType() == UIComponent::node) {
         Node* n = dynamic_cast<Node*>(uiComp);
         Vector2* coord = n->getCoordinates();
         curve.push_back(new Vector3(coord->x, coord->y, 1));
      }
   }

   modelingCurve->setPoints(curve);

   if (curve.size() > 0)
      sweepCurve->setCurve(modelingCurve);
}

void UIManager::addNode() {
   if (nodeCounter <= NODE_MAX) {
      Node* n = new Node(screenWidth*0.25, screenHeight*0.5, nodeRadius);
      n->setLimit(screenWidth*0.48, screenHeight - btnHeight*3 - 4*btnSpacingY);
      components.push_back(n);
      nodeCounter++;
   }
}

void UIManager::removeNode() {
   for (UIComponent* uiComp : components) {
      if (uiComp->getType() == UIComponent::node) {
         Node* n = dynamic_cast<Node*>(uiComp);
         if (n->getState() == Node::hovered) {
            components.remove(uiComp);
            nodeCounter--;
         }
      }
   }
}

void UIManager::showFps(float fps) {
   CV::color(1,0,0);
   CV::text(screenWidth*0.49,5, std::to_string((int)fps).c_str());
}
