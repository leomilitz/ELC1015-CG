#include "Background.h"

Background::Background(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
   createFirstMountain();
}

float getRandom(float low, float high)
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(low, high);
    return dis(e);
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

void Background::addMountain() {
   std::vector<Vector2*> points;
   float lastX = mountains.back()->curve->points[2]->x;
   float lastY = mountains.back()->curve->points[2]->y;
   points.push_back(new Vector2(lastX, lastY));
   points.push_back(new Vector2(lastX + screenWidth*0.2, lastY + screenHeight*(getRandom(0.1, 0.6))));
   points.push_back(new Vector2(lastX + screenWidth*0.4, lastY));
   mountains.push_back(new Mountain(new Curve(points), 0, 0.4, 0, 1));
}

void Background::createFirstMountain() {
   std::vector<Vector2*> points;

   points.push_back(new Vector2(screenWidth*0, screenHeight*0.3));
   points.push_back(new Vector2(screenWidth*0.2, screenHeight*0.5));
   points.push_back(new Vector2(screenWidth*0.4, screenHeight*0.3));
   mountains.push_back(new Mountain(new Curve(points), 0, 0.4, 0, 1));
}

void Background::drawMountains() {
   if (mountains.size() < 4)
      addMountain();

   if (getOutOfBoundsMountain() != -1)
      mountains.erase(mountains.begin() + getOutOfBoundsMountain());

   for (Mountain* m : mountains) {
      m->render();
   }
}

void Background::render() {
   drawSky();
   drawMountains();
   drawGround();
}
