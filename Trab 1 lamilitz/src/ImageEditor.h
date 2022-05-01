#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <vector>

#include "Image.h"
#include "ColorHistogram.h"

#define MAX_IMAGES 4

class ImageEditor {
   public:
      ImageEditor(ColorHistogram *histogram);
      void addImage(int x, int y, std::string path);
      void inputManagement(int mouseX, int mouseY, int mouseState);
      int  checkClickedImagesPriority(float mouseX, float mouseY);
      void renderImages();
      void deleteImage();
      void resizeImage(double scale);
      void flipHorizontal();
      void flipVertical();
      void rotateImg(int side);
      void updateHistogram();
      bool listenToImageChange();

      std::vector<Image*> &getImages();
      std::string getImageName();
      int getCurrentImageIndex();

      void setBrightness(int value);
      void setContrast(int value);
      void setColorFilter(Image::Filter filter);
      void setCurrentImage(int idx);
   private:
      std::vector<Image*> images;
      int currentIndex;
      ColorHistogram *histogram;

      bool checkUserInputError();
      bool imgChanged;
};

#endif // IMAGEEDITOR_H
