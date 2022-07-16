#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

#include <math.h>

class Vector3 {
public:
    float x, y, z;

   Vector3() {
      x = y = z = 0;
   };

   Vector3(const float _x, const float _y, const float _z) {
      x = _x;
      y = _y;
      z = _z;
   };

   Vector3(const Vector3 &v) {
      this->x = v.x;
      this->y = v.y;
      this->z = v.z;
   };

   void set(const float _x, const float _y, const float _z) {
      this->x = _x;
      this->y = _y;
      this->z = _z;
   };

   void set(const Vector3 v) {
      this->x = v.x;
      this->y = v.y;
      this->z = v.z;
   };

   Vector3 operator + (const Vector3 &v) {
      return Vector3(x + v.x, y + v.y, z + v.z);
   }

   Vector3 operator - (const Vector3 &v) {
      return Vector3(x - v.x, y - v.y, z - v.z);
   }

   Vector3 operator * (const float v) {
      return Vector3(x * v, y * v, z * v);
   }

   Vector3 operator / (const float s) {
      return Vector3(x / s, y / s, z / s);
   }

   float operator * (const Vector3 &v) {
      return (x * v.x + y * v.y + z * v.z);
   }

   Vector3 operator / (const Vector3 &v) {
      return Vector3(x / v.x, y / v.y, z / v.z);
   }

   bool operator > (const Vector3 &v) {
      return (x > v.x && y > v.y && z > v.z);
   }

   bool operator < (const Vector3 &v) {
      return (x < v.x && y < v.y && z < v.z);
   }

   float norm() {
      return (float)(sqrt(x * x + y * y + z * z));
   }

   void normalize() {
      float norm = this->norm();
      if (norm == 0) {
         this->x = 1;
         this->y = 1;
         this->z = 1;
      }
      else {
         this->x /= norm;
         this->y /= norm;
         this->z /= norm;
      }
   }

   Vector3 normalized() {
      float norm = this->norm();
      return ((norm == 0) ? Vector3(1, 1, 1) : Vector3(x / norm, y / norm, z / norm));
   }
};

#endif
