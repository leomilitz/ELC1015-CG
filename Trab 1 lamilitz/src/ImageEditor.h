#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <vector>

#include "Image.h"

class ImageEditor {
   public:
      std::vector<Image*> images;

      ImageEditor();
      void addImage(float x, float y);
      void setCurrentImage(int idx);
      int checkClickedImagesPriority(float mouseX, float mouseY);
   private:
      int currentIndex;
};

#endif // IMAGEEDITOR_H
