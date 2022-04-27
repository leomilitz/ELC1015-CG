#include "ImageEditor.h"

ImageEditor::ImageEditor() {
   currentIndex = 0;
}

void ImageEditor::addImage(float x, float y) {
   if (images.size() < 3) {
      images.push_back(new Image(".\\Trab 1 lamilitz\\resources\\normal_1.bmp", currentIndex, x, y));
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
   if (images.size() == 0) return;

   for (Image* image : images) {
      if (image != NULL)
         image->imgRender();
   }
}

void ImageEditor::inputManagement(float mouseX, float mouseY, int mouseState) {
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

   int idx = getCurrentImageIndex();

   if (idx == -1) {
      printf("\nThere are no images selected.");
      return true;
   }

   return false;
}

void ImageEditor::deleteImage() {
   if (checkUserInputError())
      return;

   for (Image* img : images) {
      if (img->isCurrentImg()) {
         images.erase(images.begin()+img->getIndex());
         currentIndex--;
      }
   }
}

void ImageEditor::setColorFilter(Image::Filter filter) {
   if (checkUserInputError())
      return;

   int idx = getCurrentImageIndex();
   images[idx]->setFilter(filter);
}

void ImageEditor::resizeImage(double scale) {
   if (checkUserInputError())
      return;

   int idx = getCurrentImageIndex();
   images[idx]->resizeImage(scale);
}

void ImageEditor::flipHorizontal() {
   if (checkUserInputError())
      return;

   int idx = getCurrentImageIndex();
   images[idx]->flipHorizontal();
}

void ImageEditor::flipVertical() {
   if (checkUserInputError())
      return;

   int idx = getCurrentImageIndex();
   images[idx]->flipVertical();
}

void ImageEditor::rotateImg(int side) {
   if (checkUserInputError())
      return;

   int idx = getCurrentImageIndex();
   images[idx]->rotateImg(side);
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
