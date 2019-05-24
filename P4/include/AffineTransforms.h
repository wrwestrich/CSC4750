#if !defined AFFINE_TRANSFORMS_H
#define AFFINE_TRANSFORMS_H

#include "Matrix.h"
#include "Vertex.h"
#include "Vector.h"
using CSC1310::Matrix;

class AffineTransforms
{
	private:

	public:
		static Matrix* camera(Vertex*, Vertex*, Vector*);
		static Matrix* normal(double, double);
		static Matrix* rotate(double, double, double);
		static Matrix* rotateX(double);
		static Matrix* rotateY(double);
		static Matrix* rotateZ(double);
		static Matrix* translate(double, double, double);
		static Matrix* window(int, int);
		static Matrix* scale(double, double, double);
};

#endif
