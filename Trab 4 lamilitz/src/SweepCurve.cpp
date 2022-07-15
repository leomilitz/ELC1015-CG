#include "SweepCurve.h"

SweepCurve::SweepCurve(Curve* curve, float x, float y, float cameraOffset) {
   this->curve = curve;
   this->cameraOffset = cameraOffset;
   dist = cameraOffset;
   sweepDivisor = 30;
   pointInc = 0.09;
   posX = x;
   posY = y;
   angleX = 0;
   angleY = 0;
   mouseX = 0;
   mouseY = 0;
   thetaX = 0;
   thetaY = 0;
   isRotating = false;
   isHolding  = false;
   isOrtho    = false;
   speed = 1.5;
   sweepMode = translateY;
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
   float offset = 0;

   if (p.z == 0) {
      z = 1;
   }

   if (isOrtho) {
      z = 1;
      offset = 0;
   } else {
      offset = cameraOffset;
   }

   return Vector2(p.x*dist/(z + offset) , p.y*dist/(z + offset));
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
         CV::translate(0,0);
         if (isHolding) {
            mesh[i][j] = rotateX3D(mesh[i][j]);
            mesh[i][j] = rotateY3D(mesh[i][j]);
         }

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
   thetaX = 0; thetaY = 0;
}

Vector3 SweepCurve::rotateX3D(Vector3 p) {
   float ang = thetaX*speed/fps;
   float x = cos(ang)*p.x + sin(ang)*p.z;
   float y = p.y;
   float z = cos(ang)*p.z - sin(ang)*p.x;

   return Vector3(x, y, z);
}

Vector3 SweepCurve::rotateY3D(Vector3 p) {
   float ang = thetaY*speed/fps;
   float x = p.x;
   float y = cos(ang)*p.y - sin(ang)*p.z;
   float z = sin(ang)*p.y + cos(ang)*p.z;

   return Vector3(x, y, z);
}

std::vector<Vector3> SweepCurve::calculateSweep(float angle) {
   std::vector<Vector3> curve;

   for (Vector3* p : points) {
      float x = p->x*cos(angle);
      float z = p->z*sin(angle);

      curve.push_back(Vector3(x, p->y, z));
   }

   return curve;
}

std::vector<std::vector<Vector3>> SweepCurve::createMesh() {
   std::vector<std::vector<Vector3>> matrix;

   Vector3 mid = getMidPoint(points);
   for (unsigned int i = 0; i < points.size(); i++) {
      float distFromY = points[i]->x;
      points[i]->x = points[i]->x - mid.x;
      points[i]->y = points[i]->y - mid.y;

      switch (sweepMode) {
         case translateY:  points[i]->x = points[i]->z = distFromY;  break;
         case selfRotate:  points[i]->z = points[i]->x;              break;
      }
   }

   for (int i = 0; i <= sweepDivisor; i++) {
      float angle = i*PI*2/sweepDivisor;
      matrix.push_back(calculateSweep(angle));
   }

   return matrix;
}

void SweepCurve::mouseInputManagement(int button, int *state, int wheel, int direction, int mouseX, int mouseY, int div) {
   float increaseVal = cameraOffset*0.1;
   if (isOrtho)
      increaseVal = cameraOffset*0.0001;

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

   if (isHolding) {
      // Diferença entre a posição do mouse no frame atual pro frame anterior.
      thetaX = mouseX - this->mouseX;
      thetaY = mouseY - this->mouseY;
   }

   this->mouseX = mouseX;
   this->mouseY = mouseY;
}

void SweepCurve::render(float fps) {
   this->fps = fps;

   if (curve->points.size() <= 1) return;

   points = curve->getDiscreteCurve(pointInc);

   if (!isHolding)
      mesh = createMesh();

   CV::color(1,1,1);
   drawWireFrame();
   CV::translate(0,0);
}

void SweepCurve::setCurve(Curve* curve) {
   this->curve = curve;
}

std::string SweepCurve::changePerspective() {
   isOrtho = !isOrtho;

   if (isOrtho) {
      dist = dist / cameraOffset;
      return "Orthographic";
   } else {
      dist = dist * cameraOffset;
      return "Perspective";
   }
}

std::string SweepCurve::changeSweepMode() {
   std::string modeString = "";
   switch (sweepMode) {
      case translateY:
         sweepMode = selfRotate;
         modeString = "Self Rotate";
         break;
      case selfRotate:
         sweepMode  = translateY;
         modeString = "Translate Y";
         break;
   }

   return modeString;
}

std::string SweepCurve::addSweepDivisor(int div) {
   int newDiv = sweepDivisor + div;
   if (newDiv >= 3 && newDiv <= 50)
      sweepDivisor = newDiv;
   return std::to_string(sweepDivisor);
}

std::string SweepCurve::addPoints(float div) {
   float newPointDiv = pointInc + div;
   if (newPointDiv > 0.01 && newPointDiv < 0.33)
      pointInc = newPointDiv;
   return std::to_string((int) floor(1/pointInc));
}


SweepCurve::~SweepCurve() {}
