#include "Image.h"

void Image::modelData() {
   uchar* img = bmp->getImage();
   data.resize(bmp->getHeight() * bmp->getWidth());
   for (int i = 0; i < bmp->getHeight(); i++) {
      for (int j = 0; j < bmp->getWidth()*3; j+=3) {
         int idx = (i*width*3) + j;
         data[(i*bmp->getWidth()) + j/3] = new Pixel(img[idx+2], img[idx+1], img[idx]);
      }
   }
}

Image::Image(std::string path, int idx, float x, float y) {
   imgPath = path;
   bmp = new Bmp(path.c_str());
   width = bmp->getWidth();
   height = bmp->getHeight();
   modelData();
   pos1 = new Vector2(0,0);
   pos2 = new Vector2(0,0);
   offset = new Vector2(0,0);
   updatePosition(x, y);
   isCurrent = false;
   isHolding = false;
   outline = 10;
   index = idx;
   imgState = standard;
   activeFilters.push_back(red);
   activeFilters.push_back(green);
   activeFilters.push_back(blue);
   brightness = 0.0;
}

float Image::truncateColor(float val) {
   if (val < 0) return 0.0;
   if (val > 1) return 1.0;
   return val;
}

bool Image::checkCollision(float mouseX, float mouseY) {
   Vector2 mouse; mouse.x = mouseX; mouse.y = mouseY;
   return (*pos1 <= mouse && *pos2 >= mouse);
}

Image::State Image::getImgState(float mouseX, float mouseY, int mouseState) {
   Vector2* posMouse = new Vector2(mouseX, mouseY);
   imgState = standard;

   if (*pos1 <= *posMouse && *pos2 >= *posMouse) {
      imgState = hovered;

      if (mouseState == 1) {
         isCurrent = true;
         isHolding = false;
         imgState = clicked;
      }

      if (mouseState == 0 && !isHolding) {
         isHolding = true;
         Vector2 _offset = *posMouse - *pos1;
         offset->x = _offset.x; offset->y = _offset.y;
         imgState = holding;
      }
   }

   imgDragAround(posMouse);

   return imgState;
}

void Image::imgRender() {
   if (bmp != NULL && data.size() > 0) {
      // outline
      if (isCurrent && isFront) {
         imgDrawSelectionOutline();
      }

      if (!isCurrent && imgState == hovered) {
         imgDrawHoveringOutline();
      }

      for (int i = 0; i < height; i ++) {
         for (int j = 0; j < width; j++) {
            int idx = i*width + j;
            float r = 0, g = 0, b = 0;
            for (Filter f : activeFilters) {
               switch (f) {
                  case red:       r = data[idx]->r / 255.0;                   break;
                  case green:     g = data[idx]->g / 255.0;                   break;
                  case blue:      b = data[idx]->b / 255.0;                   break;
                  case luminance: r = g = b = 0.299*r + 0.587*g + 0.113*b;    break;
                  case inverted:  r = 1 - r; g = 1 - g; b = 1 - b;            break;
                  case bgr:       r = r + b; b = r - b; r = r - b;            break;
               }
            }

            r = truncateColor(r + brightness);
            g = truncateColor(g + brightness);
            b = truncateColor(b + brightness);

            CV::color(r,g,b);
            CV::point(pos1->x + j, pos1->y + i);
         }
      }
   }
}

void Image::updatePosition(float x, float y) {
   pos1->x = x; pos1->y = y;
   pos2->x = pos1->x + width;
   pos2->y = pos1->y + height;
}

void Image::imgDragAround(Vector2* posMouse) {
   if (isCurrent && isFront && isHolding) {
      Vector2 newPos = *posMouse - *offset;
      updatePosition(newPos.x, newPos.y);
   }
}

void Image::imgDrawSelectionOutline() {
   for (int i=1; i <= outline; i++) {
      float alpha = 1.0 - ((float) i / outline);
      CV::color(1.0, 0.2, 0.2, alpha);
      CV::line(pos1->x - i, pos1->y - i, pos1->x - i, pos2->y + i); // lado esquerdo
      CV::line(pos1->x - i, pos2->y + i, pos2->x + i, pos2->y + i); // cima
      CV::line(pos2->x + i, pos2->y + i, pos2->x + i, pos1->y - i); // direita
      CV::line(pos2->x + i, pos1->y - i, pos1->x - i, pos1->y - i); // baixo
   }
}

void Image::imgDrawHoveringOutline() {
   for (int i=1; i <= 3; i++) {
      float alpha = 1.0 - ((float) i / outline);
      CV::color(0.2, 0.2, 1, alpha);
      CV::line(pos1->x - i, pos1->y - i, pos1->x - i, pos2->y + i); // lado esquerdo
      CV::line(pos1->x - i, pos2->y + i, pos2->x + i, pos2->y + i); // cima
      CV::line(pos2->x + i, pos2->y + i, pos2->x + i, pos1->y - i); // direita
      CV::line(pos2->x + i, pos1->y - i, pos1->x - i, pos1->y - i); // baixo
   }
}

void Image::setFilter(Filter filter) {
   int idx = -1;
   for (Filter f : activeFilters) {
      if (f == filter)
         idx = std::distance(activeFilters.begin(), std::find(activeFilters.begin(), activeFilters.end(), filter));
   }

   if (idx == -1) {
      if (filter == red || filter == green || filter == blue)
         activeFilters.insert(activeFilters.begin(), filter);
      else
         activeFilters.push_back(filter);
   }
   else activeFilters.erase(activeFilters.begin() + idx);
}

// Algoritmo Nearest Neighbor
void Image::resizeImage(double scale) {
   int h1 = height, w1 = width;
   int h2 = h1*scale, w2 = w1*scale;

   if (h2 > bmp->getHeight()*2 || w2 > bmp->getWidth()*2) return;

   std::vector<Pixel*> temp(h2*w2);
   double xRatio = w1/(double) w2;
   double yRatio = h1/(double) h2;
   double px, py;
   for (int i = 0; i < h2; i++) {
      for (int j = 0; j < w2; j++) {
         px = floor(j*xRatio);
         py = floor(i*yRatio);
         int idx = i*w2 + j;
         int nearest = (int)((py*w1) + px);
         temp[idx] = data[nearest];
      }
   }

   width  = w2;
   height = h2;
   pos2->x = pos1->x + width;
   pos2->y = pos1->y + height;
   data = temp;
}

void Image::flipHorizontal() {
   for (int i = 0; i < height; i++) {
      int left  = i*width;
      int right = width*(i+1) - 1;
      while(left <= right) {
         std::swap(data[left], data[right]);
         left++;
         right--;
      }
   }
}

void Image::flipVertical() {
   for (int i = 0; i < width; i++) {
      for (int j = 0; j < floor(height/2); j++) {
         int inv = height - 1 - j;
         std::swap(data[j*width + i], data[inv*width + i]);
      }
   }
}

void Image::rotateImg(int side) {
   for (int i = 0; i < height; ++i) {
      for (int j = i+1; j < width; ++j) {
         int idx1 = (i*width)  + j;
         int idx2 = (j*height) + i;
         std::swap(data[idx2], data[idx1]);
      }
   }

   (side) ? flipVertical() : flipHorizontal();
}

void Image::setIndex(int idx) { index = idx; };
void Image::setImgFront(bool isFront) { this->isFront = isFront; };
void Image::setCurrent(bool isCurrent) { this->isCurrent = isCurrent; }
bool Image::isCurrentImg() { return isCurrent; };
int Image::getIndex() { return index; };
std::vector<Image::Filter> Image::getActiveFilters() { return activeFilters; };

