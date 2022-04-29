#include "ImageEditor.h"

#define MAX_IMAGES 3

ImageEditor::ImageEditor(ColorHistogram* histogram) {
   currentIndex = 0;
   this->histogram = histogram;
}

void ImageEditor::addImage(int x, int y) {
   if (images.size() < MAX_IMAGES) {
      images.push_back(new Image(".\\Trab 1 lamilitz\\resources\\arizona.bmp", currentIndex, x, y));
      setCurrentImage(currentIndex);
      currentIndex++;
   } else {
      printf("\nlimite de 3 imagens atingido");
   }
}

int ImageEditor::checkClickedImagesPriority(float mouseX, float mouseY) {
   std::vector<int> imageIndexes;

   for (Image* image : images) {
      if (image->checkCollision(mouseX, mouseY)) {
         imageIndexes.push_back(image->getIndex());
      }
   }

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

   int last = images.size() - 1; // ultima imagem a ser renderizada já está na frente
   if (idx != last) {
      images[idx]->setIndex(last);
      images[last]->setIndex(idx);
      std::swap(images[last], images[idx]);
   }
}

void ImageEditor::renderImages() {
   histogram->draw();
   if (images.size() == 0) return;

   for (Image* image : images) {
      if (image != NULL)
         image->imgRender();
   }
}

void ImageEditor::inputManagement(int mouseX, int mouseY, int mouseState) {
   imgChanged = false;
   for (Image* image : images) {
      if (image != NULL) {
         Image::State st = image->getImgState(mouseX, mouseY, mouseState);

         if (mouseState == 1 && st == Image::clicked) {
            int idx = checkClickedImagesPriority(mouseX, mouseY);
            setCurrentImage(idx);
            imgChanged = true;
         }
      }
   }
}

bool ImageEditor::checkUserInputError() {
   if (images.size() == 0) {
      printf("\nThere are no images in the editor.");
      return true;
   }

   if (getCurrentImageIndex() == -1) {
      printf("\nThere are no images selected.");
      return true;
   }

   return false;
}

void ImageEditor::deleteImage() {
   if (checkUserInputError()) return;

   for (Image* img : images) {
      if (img->isCurrentImg()) {
         images.erase(images.begin()+img->getIndex());
         currentIndex--;
      }
   }
}

void ImageEditor::setColorFilter(Image::Filter filter) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->setFilter(filter);
   updateHistogram();
}

void ImageEditor::setBrightness(int value) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->setBrightness(value);
   updateHistogram();
}

void ImageEditor::setContrast(int value) {
   if (checkUserInputError()) return;
   images[getCurrentImageIndex()]->setContrast(value);
   updateHistogram();
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

   int width = images[idx]->getWidth();
   int height = images[idx]->getHeight();
   histogram->setSizeX(width);
   histogram->setSizeY(height);

   std::vector<Pixel*> data = images[idx]->getData();
   std::vector<int> valuesR(width);
   std::vector<int> valuesG(width);
   std::vector<int> valuesB(width);

   for (int i = 0; i < height; i++) {
      int rCount = 0, gCount = 0, bCount = 0;

      for (int j = 0; j < width; j++) {
         int r = data[j*width + i]->r;
         int g = data[j*width + i]->g;
         int b = data[j*width + i]->b;

         if (r > (r + g + b)/3) rCount++;
         if (g > (r + g + b)/3) gCount++;
         if (b > (r + g + b)/3) bCount++;
      }

      valuesR[i] = rCount;
      valuesG[i] = gCount;
      valuesB[i] = bCount;
   }

   histogram->setColorValues(valuesR, 'r');
   histogram->setColorValues(valuesG, 'g');
   histogram->setColorValues(valuesB, 'b');
}

int ImageEditor::getCurrentImageIndex() {
   for (Image* img : images) {
      if (img->isCurrentImg()) {
         return img->getIndex();
      }
   }

   return -1;
}

bool ImageEditor::listenToImageChange() { return imgChanged; }
std::vector<Image*> ImageEditor::getImages() { return images; };
