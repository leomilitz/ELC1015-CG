#ifndef SWEEPCURVE_H
#define SWEEPCURVE_H

#include <vector>
#include <string>

#include "Curve.h"
#include "Vector3.h"

class SweepCurve
{
   public:

      SweepCurve(Curve* curve, float x, float y, float cameraOffset);
      virtual ~SweepCurve();

      void render(float fps);
      void mouseInputManagement(int button, int *state, int wheel, int direction, int mouseX, int mouseY, int div);
      void setCurve(Curve* curve);
      std::string addPoints(float div);
      std::string addSweepDivisor(int div);
      std::string changePerspective();
      std::string changeSweepMode();

   private:
      enum SweepMode { selfRotate, translateY };

      Vector3 getMidPoint(std::vector<Vector3*> &points);
      Vector3 rotationalSweep(Vector3 point);
      Vector3 rotateX3D(Vector3 p);
      Vector3 rotateY3D(Vector3 p);
      Vector2 createProjection(Vector3 p);
      void drawMesh();
      void drawWireFrame();
      std::vector<std::vector<Vector3>> createMesh();
      std::vector<Vector3> calculateSweep(float angle);

      std::vector<Vector3*> points;
      std::vector<std::vector<Vector3>> mesh;
      Curve* curve;
      int sweepDivisor;
      float fps, pointInc, thetaX, thetaY;
      float posX, posY, dist, angleX, angleY;
      int mouseX, mouseY, mouseOffsetX, mouseOffsetY;
      bool isRotating, isOrtho, isHolding;
      float speed, cameraOffset;
      SweepMode sweepMode;

};

#endif // SWEEPCURVE_H
