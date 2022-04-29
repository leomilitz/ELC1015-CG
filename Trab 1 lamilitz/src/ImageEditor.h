#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <vector>

#include "Image.h"

class ImageEditor {
   public:
      ImageEditor();
      void addImage(int x, int y);
      int checkClickedImagesPriority(float mouseX, float mouseY);
      void inputManagement(int mouseX, int mouseY, int mouseState);
      void renderImages();
      void deleteImage();
      void resizeImage(double scale);
      bool listenToImageChange();
      void flipHorizontal();
      void flipVertical();
      void rotateImg(int side);
      void setBrightness(int value);
      void setContrast(int value);

      std::vector<Image*> getImages();
      int getCurrentImageIndex();
      void setColorFilter(Image::Filter filter);
      void setCurrentImage(int idx);
   private:
      std::vector<Image*> images;
      int currentIndex;

      bool checkUserInputError();
      bool imgChanged;
};

#endif // IMAGEEDITOR_H
