#if !defined VERTEX_H
#define VERTEX_H

#include "Color.h"
#include "Matrix.h"
#include "Vector.h"
using CSC1310::Matrix;

class Vertex
{
   private:
      Matrix* vertex;
      Color* color;
     
   public:
      Vertex(double x, double y, double z);
      virtual ~Vertex();
      void setX(double x);
      void setY(double y);
      void setZ(double z);
      void setH(double h);
      double getX();
      double getY();
      double getZ();
      double getH();
      void setRed(double x);
      void setGreen(double y);
      void setBlue(double z);
      double getRed();
      double getGreen();
      double getBlue();
      Vertex* multiply(Matrix* matrix);
	  Vector* sub(Vertex*);
	  void homogenize();
	  double dot(Vector*);
      void displayVertex();
};

#endif
