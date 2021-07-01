#if !defined (AFFINETRANSFORMS_H)
#define AFFINETRANSFORMS_H

#include "Vertex.h"
#include "Vector.h"

class AffineTransforms
{
   private:
      static double PI;

   public:
      static Matrix* cameraTransform(Vertex* eyepoint, Vertex* atpoint, Vector* up);
      static Matrix* perspectiveNorm(double xmax, double ymax, double zmax, double zmin);
      static Matrix* window(int xPixels, int yPixels);
      static Matrix* translate(double x, double y, double z);
      static Matrix* scale(double x, double y, double z);
      static Matrix* rotateX(double degrees);
      static Matrix* rotateY(double degrees);
      static Matrix* rotateZ(double degrees);
};

#endif
