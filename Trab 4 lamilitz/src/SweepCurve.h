#ifndef SWEEPCURVE_H
#define SWEEPCURVE_H

#include <vector>

#include "Curve.h"
#include "Vector3.h"

class SweepCurve
{
   public:
      SweepCurve(Curve* curve, float x, float y);
      virtual ~SweepCurve();

      void render(float fps);
      void setCurve(Curve* curve);

   private:
      Vector3 getMidPoint(std::vector<Vector3*> &points);
      Vector3 rotationalSweep(Vector3 point);
      Vector2 createProjection(Vector3 p);
      void drawMesh();
      void drawWireFrame();
      std::vector<std::vector<Vector3>> createMesh();
      std::vector<Vector3> calculateSweep(float angle);

      std::vector<Vector3*> points;
      std::vector<std::vector<Vector3>> mesh;
      Curve* curve;
      int sweepDivisor;
      float fps;
      float posX, posY, dim;

};

#endif // SWEEPCURVE_H
