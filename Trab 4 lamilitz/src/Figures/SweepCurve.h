#ifndef SWEEPCURVE_H
#define SWEEPCURVE_H

#include <vector>
#include <string>

#include "Curve.h"
#include "Utils/Vector3.h"

class SweepCurve {
   public:
      SweepCurve(Curve* curve, float x, float y, Vector2 cameraOffset, float axisOffset);
      virtual ~SweepCurve();

      void render(float fps);
      void mouseInputManagement(int button, int *state, int wheel, int direction, int mouseX, int mouseY, int div);
      void keyboardInputManagement(int key, bool keyUp);
      void setCurve(Curve* curve);
      std::string addPoints(float div);
      std::string addSweepDivisor(int div);
      std::string changePerspective();
      std::string changeRotationMode();
      std::string translateY(int value);
      std::string addSweepLaps(int value);

   private:
      enum RotationMode { selfRotate, translateAxis };

      Vector3 getMidPoint(std::vector<Vector3*> &points);
      Vector3 rotationalSweep(Vector3 point);
      Vector3 rotateX3D(Vector3 p);
      Vector3 rotateY3D(Vector3 p);
      Vector2 createProjection(Vector3 p);
      void drawWireFrame();
      std::vector<std::vector<Vector3>> createMesh();
      std::vector<Vector3> calculateSweep(float angle, float translation);

      std::vector<Vector3*> points;
      std::vector<std::vector<Vector3>> mesh;
      Curve* curve;
      int sweepDivisor;
      float fps, pointInc, thetaX, thetaY;
      float posX, posY, dist, angleX, angleY;
      int mouseX, mouseY, mouseOffsetX, mouseOffsetY, sweepLaps;
      bool isRotating, isOrtho, isHolding;
      float speed, cameraSpeed, axisOffset, translationValue;
      Vector2 cameraOffset;
      RotationMode rotationMode;
};

#endif // SWEEPCURVE_H
