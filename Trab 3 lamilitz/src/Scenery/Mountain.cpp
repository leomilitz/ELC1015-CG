#include "Mountain.h"

Mountain::Mountain(Curve *curve, float r, float g, float b, float speed) {
   this->curve = curve;
   this->r = r; this->g = g; this->b = b;
   this->speed = speed;
}

void Mountain::render() {
   CV::color(r,g,b);
   curve->renderBezierFill();
   curve->sumAll(-speed);
}
