#ifndef SWEEPCURVE_H
#define SWEEPCURVE_H

#include <vector>
#include <string>

#include "Curve.h"
#include "Vector3.h"

class SweepCurve
{
   public:
      SweepCurve(Curve* curve, float x, float y);
      virtual ~SweepCurve();

      void render(float fps);
      void inputManagement(int button, int *state, int wheel, int direction, int mouseX, int mouseY, int div);
      void setCurve(Curve* curve);
      std::string addSweepDivisor(int div);
      std::string changePerspective();

   private:
      Vector3 getMidPoint(std::vector<Vector3*> &points);
      Vector3 rotationalSweep(Vector3 point);
      Vector2 createProjection(Vector3 p);
      void drawMesh();
      void drawWireFrame();
      std::vector<std::vector<Vector3>> createMesh();
      std::vector<Vector3> calculateSweep(float angle, float radius);

      std::vector<Vector3*> points;
      std::vector<std::vector<Vector3>> mesh;
      Curve* curve;
      int sweepDivisor;
      float fps;
      float posX, posY, dist;
      int mouseX, mouseY;
      bool isRotating, isOrtho;

};

#endif // SWEEPCURVE_H
