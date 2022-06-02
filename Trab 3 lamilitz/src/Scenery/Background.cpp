#include "Background.h"

Background::Background(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;
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

void Background::render() {
   drawSky();
   drawGround();
}
