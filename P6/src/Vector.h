#if !defined (VECTOR_H)
#define VECTOR_H

#include "Matrix.h"
using CSC1310::Matrix;

class Vector
{
   private:
      Matrix* vector;
	  double mag;

   public:
      Vector(double x, double y, double z);
      ~Vector();
      void setX(double x);
      void setY(double y);
      void setZ(double z);
      double getX();
      double getY();
      double getZ();
      void printVector();
	  double dot(Vector*);
	  Vector* cross(Vector*);
	  Vector* norm();
	  Vector* mult(double);
     Vector* div(double);
	  Vector* add(Vector*);
     Vector* sub(Vector*);
     double getLength();
};

#endif
