#include "ImageEditor.h"

ImageEditor::ImageEditor(ColorHistogram* histogram) {
   currentIndex = 0;
   this->histogram = histogram;
}

void ImageEditor::addImage(int x, int y, std::string path) {
   if (images.size() < MAX_IMAGES) {
      images.push_back(new Image(path, currentIndex, x, y));
      setCurrentImage(currentIndex);
      defineImgCollisions(images[currentIndex]);
      currentIndex++;
   }
}

int ImageEditor::checkClickedImagesPriority(float mouseX, float mouseY) {
   std::vector<int> imageIndexes;

   for (Image* image : images)
      if (image->checkCollision(mouseX, mouseY))
         imageIndexes.push_back(image->getIndex());

   int frontIdx = imageIndexes.size() - 1;

   if (imageIndexes.size() > 0)
      return imageIndexes[frontIdx];

   return -1;
}

void ImageEditor::setCurrentImage(int idx) {
   for (Image* image : images) {
      if (image->getIndex() != idx) {
         image->setCurrent(false);
         image->setImgFront(false);
      } else
         image->setImgFront(true);
   }

   int last = images.size() - 1;
   if (idx != last) {
      images[idx]->setIndex(last);
      images[last]->setIndex(idx);
      std::swap(images[last], images[idx]);
   }
}

void ImageEditor::defineImgCollisions(Image* img) {
   img->setLimitX(collisionX);
   img->setLimitY(collisionY);
}

void ImageEditor::renderImages() {
   histogram->draw();

   if (images.size() == 0) return;

   for (Image* image : images)
      image->imgRender();

   updateHistogram();
}

void ImageEditor::inputManagement(int mouseX, int mouseY, int mouseState) {
   imgChanged = false;
   if (images.size() == 0) return;

   for (Image* image : images) {
      if (mouseX < collisionX || mouseY > collisionY)
         image->setHolding(false);

      Image::State st = image->getImgState(mouseX, mouseY, mouseState);

      if (mouseState == 1 && st == Image::clicked) {
         setCurrentImage(checkClickedImagesPriority(mouseX, mouseY));
         imgChanged = true;
      }
   }
}

bool ImageEditor::checkUserInputError() {
   if (images.size() == 0) return true;
   if (getCurrentImageIndex() == -1) return true;
   return false;
}

void ImageEditor::setColorFilter(Image::Filter filter) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->setFilter(filter);
}

void ImageEditor::setBrightness(int value) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->setBrightness(value);
}

void ImageEditor::setContrast(int value) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->setContrast(value);
}

void ImageEditor::resizeImage(double scale) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->resizeImage(scale);
}

void ImageEditor::flipHorizontal() {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->flipHorizontal();
}

void ImageEditor::flipVertical() {
   if (checkUserInputError())return;
   images[getCurrentImageIndex()]->flipVertical();
}

void ImageEditor::rotateImg(int side) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->rotateImg(side);
}

void ImageEditor::updateHistogram() {
   int idx = getCurrentImageIndex();

   if (idx == -1) return;

   std::vector<Image::Filter> filters = images[idx]->getActiveFilters();
   bool redOn = false, greenOn = false, blueOn = false, luminanceOn = false;
   for (Image::Filter f : filters) {
      if (f == Image::Filter::red)        redOn = true;
      if (f == Image::Filter::green)      greenOn = true;
      if (f == Image::Filter::blue)       blueOn = true;
      if (f == Image::Filter::luminance)  luminanceOn = true;
   }

   std::vector<int> valuesR = images[idx]->getRGBValues('r');
   std::vector<int> valuesG = images[idx]->getRGBValues('g');
   std::vector<int> valuesB = images[idx]->getRGBValues('b');
   std::vector<int> valuesL = images[idx]->getRGBValues('l');

   int highestValue = 0;
   for (int i = 0; i <= 255; i++) {
      if (redOn && valuesR[i] > highestValue)        highestValue = valuesR[i];
      if (greenOn && valuesG[i] > highestValue)      highestValue = valuesG[i];
      if (blueOn && valuesB[i] > highestValue)       highestValue = valuesB[i];
      if (luminanceOn && valuesL[i] > highestValue)  highestValue = valuesL[i];
   }

   histogram->setSizeYScale(highestValue);
   histogram->setActiveChannels(redOn, greenOn, blueOn, luminanceOn);
   histogram->setColorValues(valuesR, 'r');
   histogram->setColorValues(valuesG, 'g');
   histogram->setColorValues(valuesB, 'b');
   histogram->setColorValues(valuesL, 'l');
}

void ImageEditor::deleteImage() {
   if (checkUserInputError()) return;

   for (Image* img : images) {
      if (img->isCurrentImg()) {
         images.erase(images.begin()+img->getIndex());
         currentIndex--;
         histogram->clearHistogram();
      }
   }
}

std::string ImageEditor::getImageName() {
   if (images.size() > 0 && getCurrentImageIndex() != -1) {
      for (Image* img : images)
         if (img->isCurrentImg())
            return img->getImgName();
   }

   return "";
}

int ImageEditor::getCurrentImageIndex() {
   for (Image* img : images)
      if (img->isCurrentImg())
         return img->getIndex();

   return -1;
}

bool ImageEditor::listenToImageChange() { return imgChanged; }

std::vector<Image*>& ImageEditor::getImages() { return images; };

void ImageEditor::setCollisions(int x, int y) {
   collisionX = x;
   collisionY = y;
}
