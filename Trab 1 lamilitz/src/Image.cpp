#include "Image.h"

Image::Image(std::string path, int idx, float x, float y) {
   bmp = new Bmp(path.c_str());
   imgString = bmp->getImage();
   pos1 = new Vector2(0,0);
   pos2 = new Vector2(0,0);
   offset = new Vector2(0,0);
   updatePosition(x, y);
   isCurrent = false;
   isHolding = false;
   outline = 10;
   index = idx;
   imgState = standard;
}

bool Image::checkCollision(float mouseX, float mouseY) {
   Vector2 mouse; mouse.x = mouseX; mouse.y = mouseY;
   return (*pos1 <= mouse && *pos2 >= mouse);
}

Image::State Image::imgInputManagement(float mouseX, float mouseY, int mouseState) {
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
   if (bmp != NULL && imgString != NULL) {
      // outline
      if (isCurrent && isFront) {
         imgDrawSelectionOutline();
      }

      if (!isCurrent && imgState == hovered) {
         imgDrawHoveringOutline();
      }

      // render
      for (int i = 0; i < bmp->getHeight(); i += 1 ) {
         for (int j = 0; j < bmp->getWidth() * 3; j += 3) {
            int idx = i*(bmp->getWidth()*3) + j;
            float r = (float) imgString[idx + 2] / 255;
            float g = (float) imgString[idx + 1] / 255;
            float b = (float) imgString[idx]     / 255;

            CV::color(r,g,b);
            CV::point(pos1->x + j/3, pos1->y + i);
         }
      }
   }
}

void Image::updatePosition(float x, float y) {
   pos1->x = x; pos1->y = y;
   pos2->x = pos1->x + bmp->getWidth();
   pos2->y = pos1->y + bmp->getHeight();
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

void Image::imgDragAround(Vector2* posMouse) {
   if (isCurrent && isFront && isHolding) {
      Vector2 newPos = *posMouse - *offset;
      updatePosition(newPos.x, newPos.y);
   }
}

int Image::getIndex() { return index; };
void Image::setIndex(int idx) { index = idx; };
void Image::setImgFront(bool isFront) { this->isFront = isFront; };
void Image::setCurrent(bool isCurrent) { this->isCurrent = isCurrent; }

