#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <vector>

#include "Image.h"
#include "ColorHistogram.h"

class ImageEditor {
   public:
      ImageEditor(ColorHistogram* histogram);
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

      std::vector<Image*>& getImages();
      int getCurrentImageIndex();
      void setColorFilter(Image::Filter filter);
      void setCurrentImage(int idx);
      void updateHistogram();
   private:
      std::vector<Image*> images;
      int currentIndex;
      ColorHistogram* histogram;

      bool checkUserInputError();
      bool imgChanged;
};

#endif // IMAGEEDITOR_H
