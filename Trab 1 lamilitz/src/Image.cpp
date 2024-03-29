#include "Image.h"

std::string parseFileName(std::string &path) {
   std::vector<std::string> tokens;
   std::string token;
   std::stringstream ss(path);
   while (std::getline(ss, token, '\\'))
      tokens.push_back(token);

   return tokens[tokens.size()-1];
}

Image::Image(int x, int y, std::string &path, int idx) {
   imgName = parseFileName(path);
   bmp = new Bmp(path.c_str());
   width = bmp->getWidth();
   height = bmp->getHeight();
   modelData();
   pos1 = new Vector2(0,0);
   pos2 = new Vector2(0,0);
   offset = new Vector2(0,0);
   updatePosition(x, y);
   isCurrent = true;
   isFront = true;
   isHolding = false;
   outline = 10;
   index = idx;
   imgState = standard;
   activeFilters.push_back(red);
   activeFilters.push_back(green);
   activeFilters.push_back(blue);
   redValues.resize(256);
   greenValues.resize(256);
   blueValues.resize(256);
   luminanceValues.resize(256);
   brightness = 0;
   contrast = 0;
}

void Image::modelData() {
   uchar* img = bmp->getImage();
   data.resize(bmp->getHeight() * bmp->getWidth());
   for (int i = 0; i < bmp->getHeight(); i++) {
      for (int j = 0; j < bmp->getWidth()*3; j+=3) {
         int idx = (i*width*3) + j;
         Pixel* px = new Pixel();
         px->r = img[idx+2]; px->g = img[idx+1]; px->b = img[idx];
         data[(i*bmp->getWidth()) + j/3] = px;
      }
   }
}

int Image::truncateColor(int val) {
   if (val < 0) return 0;
   if (val > 255) return 255;
   return val;
}

bool Image::checkCollision(int mouseX, int mouseY) {
   Vector2 mouse; mouse.x = mouseX; mouse.y = mouseY;
   return (*pos1 <= mouse && *pos2 >= mouse);
}

Image::State Image::getImgState(int mouseX, int mouseY, int mouseState) {
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
      if (isCurrent && isFront)
         imgDrawSelectionOutline();

      if (!isCurrent && imgState == hovered)
         imgDrawHoveringOutline();

      fill(redValues.begin(), redValues.end(), 0);
      fill(greenValues.begin(), greenValues.end(), 0);
      fill(blueValues.begin(), blueValues.end(), 0);
      fill(luminanceValues.begin(), luminanceValues.end(), 0);

      for (int i = 0; i < height; i ++) {
         for (int j = 0; j < width; j++) {
            int idx = (i*width) + j;
            float r = 0, g = 0, b = 0, l = 0;
            for (Filter f : activeFilters) {
               switch (f) {
                  case red:       r = data[idx]->r;                              break;
                  case green:     g = data[idx]->g;                              break;
                  case blue:      b = data[idx]->b;                              break;
                  case inverted:  r = 255 - r; g = 255 - g; b = 255 - b;         break;
                  case bgr:       r = r + b; b = r - b; r = r - b;               break;
                  case luminance: r = g = b = l = 0.299*r + 0.587*g + 0.113*b;   break;
               }
            }

            // Aplica Brilho
            r = truncateColor(r + brightness);
            g = truncateColor(g + brightness);
            b = truncateColor(b + brightness);

            // Aplica Contraste
            float factor = (float) (259*(contrast + 255))/(255*(259 - contrast));
            r = truncateColor(factor*(r - 128) + 128);
            g = truncateColor(factor*(g - 128) + 128);
            b = truncateColor(factor*(b - 128) + 128);

            // Guarda recorrência das cores para representar no histograma
            redValues[r]++;
            greenValues[g]++;
            blueValues[b]++;
            luminanceValues[l]++;

            CV::color(r/255.0, g/255.0, b/255.0);
            CV::point(pos1->x + j, pos1->y + i);
         }
      }
   }
}

void Image::updatePosition(int x, int y) {
   pos1->x = x; pos1->y = y;
   pos2->x = pos1->x + width;
   pos2->y = pos1->y + height;
}

void Image::imgDragAround(Vector2* posMouse) {
   if (isCurrent && isFront && isHolding) {
      Vector2 newPos = *posMouse - *offset;

      if (newPos.x >= limitX && newPos.y + height <= limitY)
         updatePosition(newPos.x, newPos.y);
      else if (newPos.x >= limitX && newPos.y + height > limitY)
         updatePosition(newPos.x, pos1->y);
      else if (newPos.x < limitX && newPos.y + height <= limitY)
         updatePosition(pos1->x, newPos.y);
   }
}

void Image::imgDrawSelectionOutline() {
   for (int i = 0; i <= outline; i++) {
      float alpha = 1.0 - ((float) i / outline);
      CV::color(1.0, 0.2, 0.2, alpha);
      CV::rect(pos1->x - i, pos1->y - i, pos2->x + i, pos2->y + i);
   }
}

void Image::imgDrawHoveringOutline() {
   for (int i = 0; i <= 3; i++) {
      float alpha = 1.0 - ((float) i / outline);
      CV::color(0.2, 0.2, 1, alpha);
      CV::rect(pos1->x - i, pos1->y - i, pos2->x + i, pos2->y + i);
   }
}

void Image::setFilter(Filter filter) {
   int idx = -1;
   for (Filter f : activeFilters)
      if (f == filter)
         idx = std::distance(activeFilters.begin(), std::find(activeFilters.begin(), activeFilters.end(), filter));

   if (idx == -1) {
      if (filter == red || filter == green || filter == blue) {
         activeFilters.insert(activeFilters.begin(), filter);
      } else {
         if (filter == luminance) {
            activeFilters.push_back(filter);
         } else {
            int lastIdx = activeFilters.size()-1;
            if (activeFilters[lastIdx] == luminance) {
               activeFilters.insert(activeFilters.begin() + lastIdx, filter);
            } else {
               activeFilters.push_back(filter);
            }
         }
      }
   } else
      activeFilters.erase(activeFilters.begin() + idx);
}

void Image::resizeImage(double scale) {
   int h1 = height, w1 = width;
   int h2 = h1*scale, w2 = w1*scale;

   if (h2 > bmp->getHeight()*2   || w2 > bmp->getWidth()*2 ||
       h2 < bmp->getHeight()*0.25 || w2 < bmp->getWidth()*0.25) return;

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
   int offsetX = (w1-w2)/2;
   int offsetY = (h1-h2)/2;


   int posX = pos1->x + offsetX;
   int posY = pos1->y + offsetY;

   if (posX < limitX) posX = limitX + 1;
   if (posY + h2 > limitY) posY = limitY - h2;

   updatePosition(posX, posY);
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

void Image::setIndex(int idx)          { this->index      = idx;       }
void Image::setImgFront(bool isFront)  { this->isFront    = isFront;   }
void Image::setCurrent(bool isCurrent) { this->isCurrent  = isCurrent; }
void Image::setContrast(int value)     { this->contrast   = value;     }
void Image::setBrightness(int value)   { this->brightness = value;     }
void Image::setLimitX(int value)       { this->limitX     = value;     }
void Image::setLimitY(int value)       { this->limitY     = value;     }
void Image::setHolding(bool value)     { this->isHolding  = value;     }

bool Image::isCurrentImg()             { return isCurrent;  }
int  Image::getIndex()                 { return index;      }
int  Image::getBrightness()            { return brightness; }
int  Image::getContrast()              { return contrast;   }
int  Image::getWidth()                 { return width;      }
int  Image::getHeight()                { return height;     }
std::string& Image::getImgName()       { return imgName;    }

std::vector<Image::Filter>& Image::getActiveFilters() {
   return activeFilters;
}

std::vector<int>& Image::getRGBValues(char color) {
   if (color == 'r') return redValues;
   if (color == 'g') return greenValues;
   if (color == 'b') return blueValues;

   return luminanceValues;
}

