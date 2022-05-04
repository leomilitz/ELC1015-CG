#include "UIManager.h"

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;

   bgLineThickness = 6;
   btnSpacingX     = 0.01*screenWidth;
   btnSpacingY     = 0.02*screenHeight;
   btnHeight       = screenHeight*0.0417;
   btnBigWidth     = screenWidth*0.2845;
   btnMedWidth     = (btnBigWidth - btnSpacingX)/2;
   btnSwitch       = (btnBigWidth - 2*btnSpacingX)/3;
   btnSmallWidth   = (btnBigWidth - 3*btnSpacingX)/4;
   collisionX      = btnBigWidth + bgLineThickness + btnSpacingX*3;
   collisionY      = screenHeight - btnHeight - btnSpacingY - bgLineThickness;

   imgEditor  = new ImageEditor(new ColorHistogram(btnSpacingX, btnSpacingY, screenWidth*0.2834, screenHeight*0.3666));
   imgEditor->setCollisions(collisionX, collisionY);

   uiCreate();
}

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   imgEditor->inputManagement(x, y, state);
   mouseX = x; mouseY = y; mouseState = state;

   for (UIComponent* uiComp : components)
      uiComp->inputManagement(mouseX, mouseY, &mouseState);
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   if (keyUp && key == 49)
      imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\arizona.bmp");

   if (keyUp && key == 50)
      imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\lena.bmp");

   if (keyUp && key == 51)
      imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\baboon.bmp");
}

void UIManager::uiRender() {
   imgEditor->renderImages();
   drawBackground();

   for (UIComponent* uiComp : components)
      uiComp->render();

   if (imgEditor->listenToImageChange())
      rememberComponents();
}

void UIManager::drawBackground() {
   CV::color(1,1,1);
   CV::rectFill(collisionX - bgLineThickness, 0, collisionX, screenHeight);
   CV::rectFill(collisionX, collisionY + bgLineThickness, screenWidth, collisionY);
   CV::text(collisionX + btnSpacingX, collisionY + btnSpacingY + bgLineThickness*2, imgEditor->getImageName().c_str());
}

void UIManager::uiCreate() {
   const char* tooltipText = "Keyboard: 1,2,3 to add images;\n\nMouse: Click the buttons to\ninteract with the selected image;";

   components.push_back(new Button(btnSpacingX, screenHeight - (btnHeight + btnSpacingY),
                         btnSpacingX + btnSwitch, (screenHeight - btnSpacingY), "A",
                         [this]() { imgEditor->addImage(collisionX + 1, 1, ".\\Trab 1 lamilitz\\resources\\arizona.bmp"); }));

   components.push_back(new Button(2*btnSpacingX + btnSwitch, screenHeight - (btnHeight + btnSpacingY),
                         2*btnSpacingX + 2*btnSwitch, screenHeight - btnSpacingY, "B",
                         [this]() { imgEditor->addImage(collisionX + 1, 1, ".\\Trab 1 lamilitz\\resources\\lena.bmp"); }));

   components.push_back(new Button(3*btnSpacingX + 2*btnSwitch, screenHeight - (btnHeight + btnSpacingY),
                         3*btnSpacingX + 3*btnSwitch, screenHeight - btnSpacingY, "C",
                         [this]() { imgEditor->addImage(collisionX + 1, 1, ".\\Trab 1 lamilitz\\resources\\baboon.bmp"); }));

   components.push_back(new Button(btnSpacingX, screenHeight - 2*(btnHeight + btnSpacingY),
                         btnSpacingX + btnBigWidth, screenHeight - (btnHeight + 2*btnSpacingY), "Delete Image",
                         [this]() { imgEditor->deleteImage(); resetComponents();}));

   components.push_back(new Button(btnSpacingX,screenHeight - 3*(btnHeight + btnSpacingY),
                         btnSpacingX + btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY), "R",
                         [this]() { imgEditor->setColorFilter(Image::Filter::red); }, Button::Color::red, true));

   components.push_back(new Button(2*btnSpacingX + btnSmallWidth, screenHeight - 3*(btnHeight + btnSpacingY),
                         2*btnSpacingX + 2*btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY), "G",
                         [this]() { imgEditor->setColorFilter(Image::Filter::green); }, (Button::Color) Button::Color::green, true));

   components.push_back(new Button(3*btnSpacingX + 2*btnSmallWidth, screenHeight - 3*(btnHeight + btnSpacingY),
                         3*btnSpacingX + 3*btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY), "B",
                         [this]() { imgEditor->setColorFilter(Image::Filter::blue); }, Button::Color::blue, true));

   components.push_back(new Button(4*btnSpacingX + 3*btnSmallWidth, screenHeight - 3*(btnHeight + btnSpacingY),
                         4*btnSpacingX + 4*btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY), "L",
                         [this]() { imgEditor->setColorFilter(Image::Filter::luminance); }, Button::Color::light, true));

   components.push_back(new Button(btnSpacingX, screenHeight - 4*(btnHeight + btnSpacingY),
                         btnSpacingX + btnMedWidth, screenHeight - (3*btnHeight + 4*btnSpacingY), "Invert",
                         [this]() { imgEditor->setColorFilter(Image::Filter::inverted); }));

   components.push_back(new Button(2*btnSpacingX + btnMedWidth, screenHeight - 4*(btnHeight + btnSpacingY),
                         2*btnSpacingX + 2*btnMedWidth, screenHeight - (3*btnHeight + 4*btnSpacingY), "BGR<->RGB",
                         [this]() { imgEditor->setColorFilter(Image::Filter::bgr); }));

   components.push_back(new Button(btnSpacingX, screenHeight - 5*(btnHeight + btnSpacingY),
                         btnSpacingX + btnMedWidth, screenHeight - (4*btnHeight + 5*btnSpacingY), "Flip Hor.",
                         [this]() { imgEditor->flipHorizontal(); }));

   components.push_back(new Button(2*btnSpacingX + btnMedWidth, screenHeight - 5*(btnHeight + btnSpacingY),
                         2*btnSpacingX + 2*btnMedWidth, screenHeight - (4*btnHeight + 5*btnSpacingY), "Flip Ver.",
                         [this]() { imgEditor->flipVertical(); }));

   components.push_back(new Button(btnSpacingX, screenHeight - 6*(btnHeight + btnSpacingY),
                         btnSpacingX + btnMedWidth, screenHeight - (5*btnHeight + 6*btnSpacingY), "Rotate Left",
                         [this]() { imgEditor->rotateImg(0); }));

   components.push_back(new Button(2*btnSpacingX + btnMedWidth, screenHeight - 6*(btnHeight + btnSpacingY),
                         2*btnSpacingX + 2*btnMedWidth, screenHeight - (5*btnHeight + 6*btnSpacingY), "Rotate Right",
                         [this]() { imgEditor->rotateImg(1); }));

   components.push_back(new Button(btnSpacingX, screenHeight - 7*(btnHeight + btnSpacingY),
                         btnSpacingX + btnMedWidth, screenHeight - (6*btnHeight + 7*btnSpacingY), "Scale 200%",
                         [this]() { imgEditor->resizeImage(2); }));

   components.push_back(new Button(2*btnSpacingX + btnMedWidth, screenHeight - 7*(btnHeight + btnSpacingY),
                         2*btnSpacingX + 2*btnMedWidth, screenHeight - (6*btnHeight + 7*btnSpacingY), "Scale 50%",
                         [this]() { imgEditor->resizeImage(0.5); }));

   components.push_back(new Tooltip(collisionX + 2*btnBigWidth + btnSmallWidth, collisionY + btnHeight, 12,
                           tooltipText, btnBigWidth + btnSmallWidth*1.4, -1, true, "?"));

   components.push_back(new Slider(-255, 255, btnSpacingX, screenHeight - 8*(btnHeight + btnSpacingY), btnBigWidth, btnHeight, "Brightness",
                         [this]() { imgEditor->setBrightness(getSlidersValues("Brightness")); }));

   components.push_back(new Slider(-255, 255, btnSpacingX, screenHeight - 9*(btnHeight + btnSpacingY), btnBigWidth, btnHeight, "Contrast",
                         [this]() { imgEditor->setContrast(getSlidersValues("Contrast")); }));
}

int UIManager::getSlidersValues(std::string componentName) {
   for (UIComponent* uiComp: components) {
      if (uiComp->getType() == UIComponent::slider && uiComp->getCaption() == componentName) {
         Slider* sld = dynamic_cast<Slider*>(uiComp);
         if (sld->canGetValue)
            return sld->getValue();
      }
   }

   return 0;
}

void UIManager::rememberComponents() {
   std::vector<Image*> images = imgEditor->getImages();
   std::vector<Image::Filter> filters = images[imgEditor->getCurrentImageIndex()]->getActiveFilters();
   for (UIComponent* uiComp : components) {
      if (uiComp->getType() == UIComponent::button) {
         Button* btn = dynamic_cast<Button*>(uiComp);

         bool hasRed       = (std::count(filters.begin(), filters.end(), Image::Filter::red) > 0);
         bool hasGreen     = (std::count(filters.begin(), filters.end(), Image::Filter::green) > 0);
         bool hasBlue      = (std::count(filters.begin(), filters.end(), Image::Filter::blue) > 0);
         bool hasLuminance = (std::count(filters.begin(), filters.end(), Image::Filter::luminance) > 0);

         if (btn->getCaption() == "R")
            (hasRed)       ? btn->setToggled(false) : btn->setToggled(true);

         if (btn->getCaption() == "G")
            (hasGreen)     ? btn->setToggled(false) : btn->setToggled(true);

         if (btn->getCaption() == "B")
            (hasBlue)      ? btn->setToggled(false) : btn->setToggled(true);

         if (btn->getCaption() == "L")
            (hasLuminance) ? btn->setToggled(false) : btn->setToggled(true);
      }

      if (uiComp->getType() == UIComponent::slider) {
         Slider* sld = dynamic_cast<Slider*>(uiComp);
         if (sld->getCaption() == "Brightness")
            sld->setValue(images[imgEditor->getCurrentImageIndex()]->getBrightness());

         if (sld->getCaption() == "Contrast")
            sld->setValue(images[imgEditor->getCurrentImageIndex()]->getContrast());
      }
   }
}

void UIManager::resetComponents() {
   for (UIComponent* uiComp : components) {
      if (uiComp->getType() == UIComponent::button) {
         Button* btn = dynamic_cast<Button*>(uiComp);
         btn->setToggled(false);
      }

      if (uiComp->getType() == UIComponent::slider) {
         Slider* sld = dynamic_cast<Slider*>(uiComp);
         sld->setValue(0);
      }
   }
}
