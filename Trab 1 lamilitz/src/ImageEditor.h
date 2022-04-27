#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <vector>

#include "Image.h"

class ImageEditor {
   public:
      ImageEditor();
      void addImage(float x, float y);
      int checkClickedImagesPriority(float mouseX, float mouseY);
      void inputManagement(float mouseX, float mouseY, int mouseState);
      void renderImages();
      void deleteImage();
      bool listenToImageChange();
      std::vector<Image*> getImages();

      int getCurrentImageIndex();
      void setColorFilter(Image::Filter filter);
      void setCurrentImage(int idx);
      void setScale(float val);
   private:
      std::vector<Image*> images;
      int currentIndex;

      bool checkUserInputError();
      bool imgChanged;
};

#endif // IMAGEEDITOR_H
