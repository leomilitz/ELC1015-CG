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
   sldManager->inputManagement(x, y, &state);

   if (imgEditor->listenToImageChange()) {
      std::vector<Image*> images = imgEditor->getImages();
      std::vector<Image::Filter> filters = images[imgEditor->getCurrentImageIndex()]->getActiveFilters();
      btnManager->setButtonState(filters);
      int brightness = images[imgEditor->getCurrentImageIndex()]->getBrightness();
      int contrast   = images[imgEditor->getCurrentImageIndex()]->getContrast();
      sldManager->setSliderState(brightness, contrast);
   }
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   this->key = key;
   this->keyUp = keyUp;
}

void UIManager::uiRender() {
   btnManager->renderButtons(mouseX, mouseY, mouseState);
   imgEditor->renderImages();
   sldManager->renderSliders();
}

void UIManager::uiCreate() {
   int btnOffsetX = 0.01*screenWidth, btnOffsetY = 0.02*screenHeight,
         btnHeight = screenHeight*0.0417, btnWidth = screenWidth*0.2845,
         smallBtnWidth = (btnWidth - 3*btnOffsetX)/4,
         medBtnWidth = (btnWidth - btnOffsetX)/2, sldLength = btnWidth;

   btnManager = new ButtonManager();
   sldManager = new SliderManager();
   imgEditor  = new ImageEditor(new ColorHistogram(btnOffsetX, btnOffsetY, screenWidth*0.2834, screenHeight*0.3666));

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - (btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + btnWidth, screenHeight - btnOffsetY), "Open Image",
                         [this]() { imgEditor->addImage(this->screenWidth*0.7, 1); });

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 2*(btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + btnWidth, screenHeight - (btnHeight + 2*btnOffsetY)), "Delete Image",
                         [this]() { imgEditor->deleteImage(); btnManager->resetButtonState(); sldManager->resetSliders(); });

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 3*(btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + smallBtnWidth, screenHeight - (2*btnHeight + 3*btnOffsetY)), "R",
                         [this]() { imgEditor->setColorFilter(Image::Filter::red); }, Button::Color::red, true);

   btnManager->addButton(new Vector2(2*btnOffsetX + smallBtnWidth, screenHeight - 3*(btnHeight + btnOffsetY)),
                         new Vector2(2*btnOffsetX + 2*smallBtnWidth, screenHeight - (2*btnHeight + 3*btnOffsetY)), "G",
                         [this]() { imgEditor->setColorFilter(Image::Filter::green); }, (Button::Color) Button::Color::green, true);

   btnManager->addButton(new Vector2(3*btnOffsetX + 2*smallBtnWidth, screenHeight - 3*(btnHeight + btnOffsetY)),
                         new Vector2(3*btnOffsetX + 3*smallBtnWidth, screenHeight - (2*btnHeight + 3*btnOffsetY)), "B",
                         [this]() { imgEditor->setColorFilter(Image::Filter::blue); }, Button::Color::blue, true);

   btnManager->addButton(new Vector2(4*btnOffsetX + 3*smallBtnWidth, screenHeight - 3*(btnHeight + btnOffsetY)),
                         new Vector2(4*btnOffsetX + 4*smallBtnWidth, screenHeight - (2*btnHeight + 3*btnOffsetY)), "L",
                         [this]() { imgEditor->setColorFilter(Image::Filter::luminance); }, Button::Color::light, true);

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 4*(btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + medBtnWidth, screenHeight - (3*btnHeight + 4*btnOffsetY)), "Invert",
                         [this]() { imgEditor->setColorFilter(Image::Filter::inverted); });

   btnManager->addButton(new Vector2(2*btnOffsetX + medBtnWidth, screenHeight - 4*(btnHeight + btnOffsetY)),
                         new Vector2(2*btnOffsetX + 2*medBtnWidth, screenHeight - (3*btnHeight + 4*btnOffsetY)), "BGR<->RGB",
                         [this]() { imgEditor->setColorFilter(Image::Filter::bgr); });

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 5*(btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + medBtnWidth, screenHeight - (4*btnHeight + 5*btnOffsetY)), "Flip Hor.",
                         [this]() { imgEditor->flipHorizontal(); });

   btnManager->addButton(new Vector2(2*btnOffsetX + medBtnWidth, screenHeight - 5*(btnHeight + btnOffsetY)),
                         new Vector2(2*btnOffsetX + 2*medBtnWidth, screenHeight - (4*btnHeight + 5*btnOffsetY)), "Flip Ver.",
                         [this]() { imgEditor->flipVertical(); });

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 6*(btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + medBtnWidth, screenHeight - (5*btnHeight + 6*btnOffsetY)), "Rotate Left",
                         [this]() { imgEditor->rotateImg(0); });

   btnManager->addButton(new Vector2(2*btnOffsetX + medBtnWidth, screenHeight - 6*(btnHeight + btnOffsetY)),
                         new Vector2(2*btnOffsetX + 2*medBtnWidth, screenHeight - (5*btnHeight + 6*btnOffsetY)), "Rotate Right",
                         [this]() { imgEditor->rotateImg(1); });

   btnManager->addButton(new Vector2(btnOffsetX, screenHeight - 7*(btnHeight + btnOffsetY)),
                         new Vector2(btnOffsetX + medBtnWidth, screenHeight - (6*btnHeight + 7*btnOffsetY)), "Scale 200%",
                         [this]() { imgEditor->resizeImage(2); });

   btnManager->addButton(new Vector2(2*btnOffsetX + medBtnWidth, screenHeight - 7*(btnHeight + btnOffsetY)),
                         new Vector2(2*btnOffsetX + 2*medBtnWidth, screenHeight - (6*btnHeight + 7*btnOffsetY)), "Scale 50%",
                         [this]() { imgEditor->resizeImage(0.5); });

   sldManager->addSlider(-255, 255, btnOffsetX, screenHeight - 8*(btnHeight + btnOffsetY), sldLength, "Brightness",
                         [this]() { imgEditor->setBrightness(sldManager->getValue()); });

   sldManager->addSlider(-255, 255, btnOffsetX, screenHeight - 9*(btnHeight + btnOffsetY), sldLength, "Contrast",
                         [this]() { imgEditor->setContrast(sldManager->getValue()); });

}

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   uiCreate();
}
