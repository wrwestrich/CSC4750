#if !defined (VECTOR_H)
#define VECTOR_H

#include "Matrix.h"
using CSC1310::Matrix;

class Vector
{
   private:
      Matrix* vector;

   public:
      Vector(double x, double y, double z);
      ~Vector();
      void setX(double x);
      void setY(double y);
      void setZ(double z);
      double getX();
      double getY();
      double getZ();
      Vector* cross(Vector* cross);
      double dot(Vector* dot);
      Vector* normalize();
      Vector* multiply(Matrix* matrix);
      void printVector();
};

#endif
