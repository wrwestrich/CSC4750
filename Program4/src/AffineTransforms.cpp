#include "AffineTransforms.h"
#include <math.h>
#include <iostream>

Matrix* AffineTransforms::scale(double x, double y, double z)
{
	Matrix* S = new Matrix(4, 4);

	S->setElement(1,1,x);
	S->setElement(1,2,0);
	S->setElement(1,3,0);
	S->setElement(1,4,0);

	S->setElement(2,1,0);
	S->setElement(2,2,y);
	S->setElement(2,3,0);
	S->setElement(2,4,0);

	S->setElement(3,1,0);
	S->setElement(3,2,0);
	S->setElement(3,3,z);
	S->setElement(3,4,0);

	S->setElement(4,1,0);
	S->setElement(4,2,0);
	S->setElement(4,3,0);
	S->setElement(4,4,1);

	return S;
}

//transform to pixel coords
Matrix* AffineTransforms::window(int xPixels, int yPixels)
{
	Matrix* W = new Matrix(4, 4);
	double nx = xPixels;
	double ny = yPixels;

	//translate (0,0) to the center of the window, and then scale to the correct size so that (1,0) is on the extreme right of the window
	W->setElement(1, 1, nx/2.0);  
	W->setElement(1, 2, 0);
	W->setElement(1, 3, 0);
	W->setElement(1, 4, (nx - 1)/2.0);

	W->setElement(2, 1, 0);
	W->setElement(2, 2, -ny/2.0);  
	W->setElement(2, 3, 0);
	W->setElement(2, 4, (ny - 1)/2.0);
   
	W->setElement(3, 1, 0);
	W->setElement(3, 2, 0);
	W->setElement(3, 3, 1);
	W->setElement(3, 4, 0);
   
	W->setElement(4, 1, 0);
	W->setElement(4, 2, 0);
	W->setElement(4, 3, 0);
	W->setElement(4, 4, 1.0);

	return W;
}

Matrix* AffineTransforms::translate(double x, double y, double z){
	
	Matrix* T = new Matrix(4,4);
	
	T->setElement(1,1,1);
	T->setElement(1,2,0);
	T->setElement(1,3,0);
	T->setElement(1,4,x);
	
	T->setElement(2,1,0);
	T->setElement(2,2,1);
	T->setElement(2,3,0);
	T->setElement(2,4,y);
	
	T->setElement(3,1,0);
	T->setElement(3,2,0);
	T->setElement(3,3,1);
	T->setElement(3,4,z);
	
	T->setElement(4,1,0);
	T->setElement(4,2,0);
	T->setElement(4,3,0);
	T->setElement(4,4,1);
	
	return T;
}

Matrix* AffineTransforms::rotate(double x, double y, double z){
		
	Matrix* RX = rotateX(x);
	Matrix* RY = rotateY(y);
	Matrix* RZ = rotateZ(z);
	
	Matrix* R1 = RY->multiply(RX);
	Matrix* R = RZ->multiply(R1);
	
	delete RX;
	delete RY;
	delete RZ;
	delete R1;
	
	return R;
	
}

Matrix* AffineTransforms::rotateX(double ang){
	
	Matrix* RX = new Matrix(4,4);
	ang = 3.1415927*ang/180.0;
	
	RX->setElement(1,1,1);
	RX->setElement(1,2,0);
	RX->setElement(1,3,0);
	RX->setElement(1,4,0);
	
	RX->setElement(2,1,0);
	RX->setElement(2,2,cos(ang));
	RX->setElement(2,3,-sin(ang));
	RX->setElement(2,4,0);
	
	RX->setElement(3,1,0);
	RX->setElement(3,2,sin(ang));
	RX->setElement(3,3,cos(ang));
	RX->setElement(3,4,0);
	
	RX->setElement(4,1,0);
	RX->setElement(4,2,0);
	RX->setElement(4,3,0);
	RX->setElement(4,4,1);
	
	return RX;
}

Matrix* AffineTransforms::rotateY(double ang){
	
	Matrix* RY = new Matrix(4,4);
	ang = 3.1415927*ang/180.0;
	
	RY->setElement(1,1,cos(ang));
	RY->setElement(1,2,0);
	RY->setElement(1,3,sin(ang));
	RY->setElement(1,4,0);
	
	RY->setElement(2,1,0);
	RY->setElement(2,2,1);
	RY->setElement(2,3,0);
	RY->setElement(2,4,0);
	
	RY->setElement(3,1,-sin(ang));
	RY->setElement(3,2,0);
	RY->setElement(3,3,cos(ang));
	RY->setElement(3,4,0);
	
	RY->setElement(4,1,0);
	RY->setElement(4,2,0);
	RY->setElement(4,3,0);
	RY->setElement(4,4,1);
	
	return RY;
}

Matrix* AffineTransforms::rotateZ(double ang){
	
	Matrix* RZ = new Matrix(4,4);
	ang = 3.1415927*ang/180.0;
	
	RZ->setElement(1,1,cos(ang));
	RZ->setElement(1,2,-sin(ang));
	RZ->setElement(1,3,0);
	RZ->setElement(1,4,0);
	
	RZ->setElement(2,1,sin(ang));
	RZ->setElement(2,2,cos(ang));
	RZ->setElement(2,3,0);
	RZ->setElement(2,4,0);
	
	RZ->setElement(3,1,0);
	RZ->setElement(3,2,0);
	RZ->setElement(3,3,1);
	RZ->setElement(3,4,0);
	
	RZ->setElement(4,1,0);
	RZ->setElement(4,2,0);
	RZ->setElement(4,3,0);
	RZ->setElement(4,4,1);
	
	return RZ;
}

Matrix* AffineTransforms::camera(Vertex* E, Vertex* A, Vector* v_up){
	
	Vector* v_up_norm = v_up->norm();
	
	Vector* N = E->sub(A);
	Vector* temp = N;
	N = N->norm();
	delete temp;
	
	double vdotN = v_up_norm->dot(N);
	double vdotN2 = vdotN * vdotN;
	double denom = sqrt(1.0 - vdotN2);
	double alpha = vdotN / denom;
	double beta = 1.0 / denom;
	
	Vector* one = N->mult(alpha);
	Vector* two = v_up_norm->mult(beta);
	Vector* V = one->add(two);
	temp = V;
	V = V->norm();
	delete temp;
	
	delete one;
	delete two;
	
	Vector* U = V->cross(N);
	temp = U;
	U = U->norm();
	delete temp;
	
	double edotU = -1.0 * E->dot(U);
	double edotV = -1.0 * E->dot(V);
	double edotN = -1.0 * E->dot(N);
	
	Matrix* cam = new Matrix(4,4);
	
	cam->setElement(1,1,U->getX());
	cam->setElement(1,2,U->getY());
	cam->setElement(1,3,U->getZ());
	cam->setElement(1,4,edotU);
	
	cam->setElement(2,1,V->getX());
	cam->setElement(2,2,V->getY());
	cam->setElement(2,3,V->getZ());
	cam->setElement(2,4,edotV);
	
	cam->setElement(3,1,N->getX());
	cam->setElement(3,2,N->getY());
	cam->setElement(3,3,N->getZ());
	cam->setElement(3,4,edotN);
	
	cam->setElement(4,1,0);
	cam->setElement(4,2,0);
	cam->setElement(4,3,0);
	cam->setElement(4,4,1);
	
	delete U;
	delete V;
	delete N;
	delete v_up_norm;
	
	return cam;
	
}

Matrix* AffineTransforms::normal(double zmin, double zmax){
	
	double alpha = (zmax + zmin) / (zmin - zmax);
	double beta = (2 * zmax * zmin) / (zmax - zmin);
	
	Matrix* norm = new Matrix(4,4);
	
	norm->setElement(1,1,1);
	norm->setElement(1,2,0);
	norm->setElement(1,3,0);
	norm->setElement(1,4,0);
	
	norm->setElement(2,1,0);
	norm->setElement(2,2,1);
	norm->setElement(2,3,0);
	norm->setElement(2,4,0);
	
	norm->setElement(3,1,0);
	norm->setElement(3,2,0);
	norm->setElement(3,3,alpha);
	norm->setElement(3,4,beta);
	
	norm->setElement(4,1,0);
	norm->setElement(4,2,0);
	norm->setElement(4,3,-1);
	norm->setElement(4,4,0);
	
	return norm;
	
}
