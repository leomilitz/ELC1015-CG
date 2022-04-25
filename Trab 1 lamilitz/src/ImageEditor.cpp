#include "ImageEditor.h"

ImageEditor::ImageEditor() {
   currentIndex = 0;
}

void ImageEditor::addImage(float x, float y) {
   if (images.size() < 3) {
      images.push_back(new Image("D:\\UFSM\\cg\\Trabs Leo\\cg-leomilitz\\Trab 1 lamilitz\\resources\\normal_1.bmp", currentIndex, x, y));
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
   for (Image* image : images) {
      if (image != NULL)
         image->imgRender();
   }
}

void ImageEditor::inputManagement(float mouseX, float mouseY, int mouseState) {
   for (Image* image : images) {
      if (image != NULL) {
         Image::State st = image->getImgState(mouseX, mouseY, mouseState);

         if (mouseState == 1 && st == Image::clicked) {
            int idx = checkClickedImagesPriority(mouseX, mouseY);
            setCurrentImage(idx);
         }
      }
   }
}

std::vector<Image*> ImageEditor::getImages() { return images; };
