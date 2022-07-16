#include "SweepCurve.h"

SweepCurve::SweepCurve(Curve* curve, float x, float y, Vector2 cameraOffset, float axisOffset) {
   this->curve = curve;
   this->cameraOffset = cameraOffset;
   this->axisOffset = axisOffset;
   dist = cameraOffset.x;
   posX = x;
   posY = y;
   mouseX = 0;
   mouseY = 0;
   thetaX = 0;
   thetaY = 0;
   sweepDivisor = 30;
   sweepLaps = 1;
   pointInc = 0.09;
   translationValue = 0;
   isHolding = false;
   isOrtho = false;
   speed = 1.5;
   cameraSpeed = 10;
   rotationMode = translateAxis;
}

SweepCurve::~SweepCurve() {}

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

   if (p.z == 0) z = 1;
   isOrtho ? z = 1 : offset = cameraOffset.x;

   return Vector2(p.x*dist/(z + offset) , p.y*dist/(z + offset));
}

void SweepCurve::drawWireFrame() {
   CV::color(1,1,1);
   CV::translate(posX, posY);

   float row = mesh.size();
   for (unsigned int i = 0; i < row; i++) {
      float col = mesh[i].size();
      for (unsigned int j = 0; j < col; j++) {
         if (isHolding) {
            mesh[i][j] = rotateX3D(mesh[i][j]);
            mesh[i][j] = rotateY3D(mesh[i][j]);
         }

         Vector2 ctrlProj = createProjection(mesh[i][j]);
         if (i < row - 1 && j < col - 1) {
            Vector2 hProjNext    = createProjection(mesh[i+1][j]);
            Vector2 vProjNext    = createProjection(mesh[i][j+1]);
            Vector2 ctrlProjDiag = createProjection(mesh[i+1][j+1]);
            CV::line(ctrlProj, hProjNext);
            CV::line(ctrlProj, vProjNext);
            CV::line(ctrlProj, ctrlProjDiag);
         }

         if (j == col - 1 && i < row - 1)
            CV::line(ctrlProj, createProjection(mesh[i+1][j]));

         if (i == row - 1 && j < col - 1)
            CV::line(ctrlProj, createProjection(mesh[i][j+1]));
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

std::vector<Vector3> SweepCurve::calculateSweep(float angle, float transation) {
   std::vector<Vector3> curve;

   for (Vector3* p : points) {
      float x = p->x*cos(angle);
      float y = p->y + transation;
      float z = p->z*sin(angle);

      curve.push_back(Vector3(x, y, z));
   }

   return curve;
}

std::vector<std::vector<Vector3>> SweepCurve::createMesh() {
   std::vector<std::vector<Vector3>> matrix;

   Vector3 mid = getMidPoint(points);
   for (unsigned int i = 0; i < points.size(); i++) {
      float distFromAxis = points[i]->x - axisOffset;
      points[i]->x = points[i]->x - mid.x;
      points[i]->y = points[i]->y - mid.y - translationValue;

      switch (rotationMode) {
         case translateAxis:  points[i]->x = points[i]->z = distFromAxis;  break;
         case selfRotate:     points[i]->z = points[i]->x;                 break;
      }
   }

   for (int i = 0; i <= sweepDivisor*sweepLaps; i++) {
      float angle = i*PI*2/sweepDivisor;
      matrix.push_back(calculateSweep(angle, translationValue*i));
   }

   return matrix;
}

void SweepCurve::mouseInputManagement(int button, int *state, int wheel, int direction, int mouseX, int mouseY, int div) {
   float increaseVal = (isOrtho) ? cameraOffset.x*0.0001 : cameraOffset.x*0.1;

   /** Zoom com a roda do mouse */
   float newDist = 0;
   if (direction == 1)
      newDist = dist + increaseVal;
   else if (direction == -1)
      newDist = dist - increaseVal;

   if (newDist > 0 && newDist < cameraOffset.x*3)
      dist = newDist;

   if (mouseX > div && button == 0 && *state == 0)
      isHolding = true;

   if (button == 0 && *state == 1)
      isHolding = false;

   if (isHolding) {
      /**
       * Faz a diferença entre a posição do mouse no frame atual pro frame anterior.
       * Com isso, é possível identificar a direção em que o mouse está se movendo
       * para calcular a rotação.
       */
      thetaX = mouseX - this->mouseX;
      thetaY = mouseY - this->mouseY;
   }

   this->mouseX = mouseX;
   this->mouseY = mouseY;
}

void SweepCurve::keyboardInputManagement(int key, bool keyUp) {
   float addVal = 0;
   if (key == 201)
      addVal = posY + cameraSpeed;

   if (key == 203)
      addVal = posY - cameraSpeed;

   if (addVal > 0 && addVal < cameraOffset.y)
      posY = addVal;
}

void SweepCurve::render(float fps) {
   this->fps = fps;
   if (curve->points.size() <= 1) return;
   points = curve->getDiscreteCurve(pointInc);

   if (!isHolding) mesh = createMesh();

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
      dist = dist / cameraOffset.x;
      return "Orthographic";
   } else {
      dist = dist * cameraOffset.x;
      return "Perspective";
   }
}

std::string SweepCurve::changeRotationMode() {
   std::string modeString = "";
   switch (rotationMode) {
      case translateAxis:
         rotationMode = selfRotate;
         modeString = "Self Rotate";
         break;
      case selfRotate:
         rotationMode  = translateAxis;
         modeString = "Translate Axis";
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

std::string SweepCurve::translateY(int value) {
   int newValue = translationValue + value;
   if (newValue >= -10 && newValue <= 10)
      translationValue = newValue;
   return std::to_string((int) floor(translationValue));
}

std::string SweepCurve::addSweepLaps(int value) {
   int newValue = sweepLaps + value;
   if (newValue >= 1 && newValue <= 4)
      sweepLaps = newValue;
   return std::to_string(sweepLaps);
}
