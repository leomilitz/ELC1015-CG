#include "SweepCurve.h"

SweepCurve::SweepCurve(Curve* curve, float x, float y) {
   this->curve = curve;
   sweepDivisor = 30;
   posX = x;
   posY = y;
   dist = 30;
   angleX = 0;
   angleY = 0;
   isRotating = false;
   isHolding  = false;
   isOrtho    = false;
}

Vector3 SweepCurve::getMidPoint(std::vector<Vector3*> &points) {
   Vector3 minCoord = *points[0];
   Vector3 maxCoord = Vector3(0,0,0);

   for (Vector3* v : points) {
      if (v->x > maxCoord.x) maxCoord.x = v->x;
      if (v->y > maxCoord.y) maxCoord.y = v->y;
      if (v->z > maxCoord.z) maxCoord.z = v->z;
      if (v->x < minCoord.x) minCoord.x = v->x;
      if (v->y < minCoord.y) minCoord.y = v->y;
      if (v->z < minCoord.z) minCoord.z = v->z;
   }

   return ((minCoord + maxCoord)*0.5);
}

Vector2 SweepCurve::createProjection(Vector3 p) {
   float z = p.z;

   if (p.z == 0)
      z = 1;

   if (isOrtho)
      z = 1;

   return Vector2(p.x*dist/z , p.y*dist/z);
}

void SweepCurve::drawMesh() {
   for (unsigned int i = 0; i < mesh.size(); i++) {
      for (unsigned int j = 0; j < mesh[i].size(); j++) {

         Vector2 projCtrl = createProjection(mesh[i][j]);
         CV::translate(posX, posY);
         CV::color(1,0,0);
         CV::point(projCtrl, 3);
      }
   }
}

void SweepCurve::drawWireFrame() {
   CV::color(1,1,1);
   float row = mesh.size();
   for (unsigned int i = 0; i < row; i++) {
      float col = mesh[i].size();
      for (unsigned int j = 0; j < col; j++) {
         CV::translate(posX, posY);
         Vector2 ctrlProj = createProjection(mesh[i][j]);

         if (i < row - 1 && j < col - 1) {
            Vector2 hProjNext = createProjection(mesh[i+1][j]);
            Vector2 vProjNext = createProjection(mesh[i][j+1]);
            Vector2 ctrlProjDiag = createProjection(mesh[i+1][j+1]);
            CV::line(ctrlProj, hProjNext);
            CV::line(ctrlProj, vProjNext);
            CV::line(ctrlProj, ctrlProjDiag);
         }

         if (j == col - 1 && i < row - 1) {
            CV::line(ctrlProj, createProjection(mesh[i+1][j]));
         }

         if (i == row - 1 && j < col - 1) {
            CV::line(ctrlProj, createProjection(mesh[i][j+1]));
         }
      }
   }
}

std::vector<Vector3> SweepCurve::calculateSweep(float angleX, float angleY, float radius) {
   std::vector<Vector3> curve;

   for (Vector3* p : points) {
      float x = p->x*cos(angleX);
      float z = radius + p->z*sin(angleX);
      curve.push_back(Vector3(x, p->y, z));
   }

   return curve;
}

std::vector<std::vector<Vector3>> SweepCurve::createMesh() {
   std::vector<std::vector<Vector3>> matrix;

   Vector3 mid = getMidPoint(points);
   for (unsigned int i = 0; i < points.size(); i++) {
      points[i]->y = points[i]->y - mid.y;
   }

   for (int i = 0; i <= sweepDivisor; i++) {
      angleX = i*PI*2/sweepDivisor;
      angleY = 0.0;
      if (isRotating && isHolding) {
         angleX += mouseX/mid.y;
         angleY += mouseY/mid.x;
      }
      float radius = 0;
      if (!isOrtho) radius = mid.x*0.125;
      matrix.push_back(calculateSweep(angleX, angleY, radius));
   }

   return matrix;
}

void SweepCurve::inputManagement(int button, int *state, int wheel, int direction, int mouseX, int mouseY, int div) {
   this->mouseX = mouseX;
   this->mouseY = mouseY;

   float increaseVal = 1;
   if (isOrtho)
      increaseVal = 0.1;

   //printf("\nbtn %d | state: %d", button, *state);

   // Zoom com a roda do mouse
   if (direction == 1) {
      dist += increaseVal;
   }
   else if (direction == -1) {
      dist -= increaseVal;
   }

   if (mouseX > div) {
      if (button == 0 && *state == 0) {
         isRotating = true;
         isHolding = true;
      }
   }

   if (button == 0 && *state == 1) {
      isRotating = false;
      isHolding = false;
   }
}

void SweepCurve::render(float fps) {
   this->fps = fps;

   if (curve->points.size() <= 1) return;

   points = curve->getDiscreteCurve(0.08);
   mesh = createMesh();

   CV::color(1,1,1);
   drawWireFrame();
   drawMesh();
   CV::translate(0,0);
}

void SweepCurve::setCurve(Curve* curve) {
   this->curve = curve;
}

std::string SweepCurve::changePerspective() {
   isOrtho = !isOrtho;

   if (isOrtho) {
      dist = dist/30;
      return "Orthographic";
   } else {
      dist = dist*30;
      return "Perspective";
   }
}

std::string SweepCurve::addSweepDivisor(int div) {
   int newDiv = sweepDivisor + div;
   if (newDiv >= 3 && newDiv <= 50)
      sweepDivisor = newDiv;
   return std::to_string(sweepDivisor);
}

SweepCurve::~SweepCurve() {}
