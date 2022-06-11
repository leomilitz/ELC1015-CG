#include "Mountain.h"

Mountain::Mountain(Curve *curve, float r, float g, float b, float speed, float speedMultiplier) {
   this->curve = curve;
   this->speed = speed;
   this->speedMultiplier = speedMultiplier;
   this->r = r; this->g = g; this->b = b;
}

void Mountain::setSpeedMultiplier(float multiplier) {
   this->speedMultiplier = multiplier;
}

void Mountain::render(float fps) {
   CV::color(r,g,b);
   curve->renderBezierFill();
   curve->sumAll(-speed*speedMultiplier/fps);
}
