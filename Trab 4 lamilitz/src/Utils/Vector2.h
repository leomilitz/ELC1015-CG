#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <math.h>
#include "Vector3.h"

class Vector2 {
   public:
      float x, y;

      Vector2() { x = y = 0; }
      Vector2(float x, float y)  { this->x = x; this->y = y; }
      void set(float x, float y) { this->x = x; this->y = y; }

      void normalize() {
         float norm = (float)sqrt(x*x + y*y);

         if(norm == 0.0) {
            x = 1;
            y = 1;
            return;
         }

         x /= norm;
         y /= norm;
      }

      float distance(const Vector2& v) {
         return sqrt(((v.x - x)*(v.x - x)) + ((v.y - y)*(v.y - y)));
      }

      Vector2 operator - (const Vector2 &v) {
         Vector2 aux(x - v.x, y - v.y);
         return(aux);
      }

      Vector2 operator + (const Vector2 &v) {
         Vector2 aux(x + v.x, y + v.y);
         return(aux);
      }

      Vector2 operator + (const float a) {
         Vector2 aux(x + a, y + a);
         return(aux);
      }

      Vector2 operator - (const float a) {
         Vector2 aux(x - a, y - a);
         return(aux);
      }

      Vector2 operator * (const float a) {
         Vector2 aux(x * a, y * a);
         return(aux);
      }

      Vector2 operator = (const Vector3 &v) {
         return Vector2(v.x, v.y);
      }

      bool operator <= (const Vector2 &v) { return( x <= v.x && y <= v.y ); }
      bool operator >= (const Vector2 &v) { return( x >= v.x && y >= v.y ); }
};

#endif
