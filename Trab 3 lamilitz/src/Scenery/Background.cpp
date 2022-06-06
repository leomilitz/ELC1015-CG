#include "Background.h"

Background::Background(int screenWidth, int screenHeight) {
   srand(time(0));
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   this->mountainSpeed = 80;
   this->buildingSpeed = 200;
   createFirstMountain();
   createFirstBuilding();
}

float getRandomInt(int lower, int upper) {
   return (rand() % (upper - lower + 1)) + lower;
}

float getRandomFloat(float lower, float upper) {
   float random = ((float) rand()) / (float) RAND_MAX;
   float diff = upper - lower;
   float r = random * diff;
   return lower + r;
}

void Background::drawGround() {
   float r = 0.6078, g = 0.4627, b = 0.3254;
   CV::color(r,g,b);
   CV::rectFill(0,screenHeight*0.2, screenWidth, screenHeight*0.15);
   CV::color(r - 0.05, g - 0.05, b - 0.05);
   CV::rectFill(0,screenHeight*0.15, screenWidth, screenHeight*0.08);
   CV::color(r - 0.08, g - 0.08, b - 0.08);
   CV::rectFill(0,screenHeight*0.08, screenWidth, screenHeight*0.03);
   CV::color(r - 0.1, g - 0.1, b - 0.1);
   CV::rectFill(0,screenHeight*0.03, screenWidth, 0);
}

void Background::drawSky() {
   float r = 0, g = 0.7, b = 0.85;
   for (int i = 0; i <= screenHeight; i++) {
      CV::color(r, g, b,((float) i / screenHeight));
      CV::line(0, i, screenWidth, i);
   }
}

int Background::getOutOfBoundsMountain() {
   int idx = 0;
   for (Mountain* m : mountains) {
      if (m->curve->points[2]->x < 0) return idx;
      idx++;
   }
   return -1;
}

int Background::getOutOfBoundsBuilding() {
   int idx = 0;
   for (Building* b : buildings) {
      if (b->posX + b->getWidth() < 0) return idx;
      idx++;
   }
   return -1;
}

void Background::addMountain() {
   std::vector<Vector2*> points;
   float lastX = mountains.back()->curve->points[2]->x;
   float lastY = mountains.back()->curve->points[2]->y;
   points.push_back(new Vector2(lastX, lastY));
   points.push_back(new Vector2(lastX + screenWidth*0.2, lastY + screenHeight*(getRandomFloat(0.25, 0.85))));
   points.push_back(new Vector2(lastX + screenWidth*0.4, lastY));
   mountains.push_back(new Mountain(new Curve(points), 0, 0.4, 0, mountainSpeed));
}
void Background::addBuilding() {
   int spacing = getRandomInt(0,20);
   int lastX = buildings.back()->posX + buildings.back()->getWidth() + spacing;
   int lastY = buildings.back()->posY;
   int width = screenWidth*(getRandomFloat(0.04,0.09));
   int height = screenHeight*(getRandomFloat(0.13, 0.35));
   float r,g,b;
   r = g = b = getRandomFloat(0.4, 0.6);
   buildings.push_back(new Building(lastX, lastY, width, height, r, g, b, buildingSpeed));
}

void Background::createFirstMountain() {
   std::vector<Vector2*> points;
   points.push_back(new Vector2(0, screenHeight*0.5));
   points.push_back(new Vector2(screenWidth*0.2, screenHeight*0.7));
   points.push_back(new Vector2(screenWidth*0.4, screenHeight*0.5));
   mountains.push_back(new Mountain(new Curve(points), 0, 0.4, 0, mountainSpeed));
}

void Background::createFirstBuilding() {
   float posX = 0, posY = screenHeight*0.2;
   float width = screenWidth*0.1;
   float height = screenHeight*(getRandomFloat(0.1, 0.4));
   float r,g,b;
   r = g = b = getRandomFloat(0.4, 0.6);
   buildings.push_back(new Building(posX, posY, width, height, r, g, b, buildingSpeed));
}

void Background::drawMountains() {
   if (mountains.size() < 4) addMountain();

   int idx = getOutOfBoundsMountain();
   if (idx != -1)
      mountains.erase(mountains.begin() + idx);

   for (Mountain* m : mountains) m->render(fps);
}

void Background::drawBuildings() {
   if (buildings.size() < 20) addBuilding();

   int idx = getOutOfBoundsBuilding();
   if (idx != -1) {
      buildings.erase(buildings.begin() + idx);
   }

   for (Building* b : buildings) b->render(fps);
}

void Background::render(float fps) {
   this->fps = fps;
   drawSky();
   drawMountains();
   drawBuildings();
   drawGround();
}
