#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <vector>

#include "Image.h"

class ImageEditor {
   public:
      ImageEditor();
      void addImage(float x, float y);
      void setCurrentImage(int idx);
      int checkClickedImagesPriority(float mouseX, float mouseY);
      void inputManagement(float mouseX, float mouseY, int mouseState);
      void renderImages();
      std::vector<Image*> getImages();

   private:
      std::vector<Image*> images;
      int currentIndex;
};

#endif // IMAGEEDITOR_H
