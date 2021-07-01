#include "Vector.h"
#include <Math.h>
#include <iostream>

Vector::Vector(double x, double y, double z)
{
   vector = new Matrix(4, 1);
   vector->setElement(1, 1, x);
   vector->setElement(2, 1, y);
   vector->setElement(3, 1, z);
   vector->setElement(4, 1, 0.0);  //4th coordinate 0 for vectors
   
   mag = sqrt((x * x) + (y * y) + (z * z));
}

Vector::~Vector()
{
   delete vector;
}

void Vector::setX(double x)
{
   vector->setElement(1, 1, x);
}

void Vector::setY(double y)
{
   vector->setElement(2, 1, y);
}

void Vector::setZ(double z)
{
   vector->setElement(3, 1, z);
}

double Vector::getX()
{
   return vector->getElement(1, 1);
}

double Vector::getY()
{
   return vector->getElement(2, 1);
}

double Vector::getZ()
{
   return vector->getElement(3, 1);
}

void Vector::printVector()
{
   vector->displayMatrix();
}

double Vector::dot(Vector* other){
	
	return ((this->getX() * other->getX()) + (this->getY() * other->getY()) + (this->getZ() * other->getZ()));
	
}

Vector* Vector::cross(Vector* other){
	
	double x = (this->getY() * other->getZ()) - (this->getZ() * other->getY());
	double y = (this->getZ() * other->getX()) - (this->getX() * other->getZ());
	double z = (this->getX() * other->getY()) - (this->getY() * other->getX());
	
	return new Vector(x, y, z);
	
}

Vector* Vector::norm(){
	
	if(mag == 1.0){
		return new Vector(this->getX(), this->getY(), this->getZ());
	}
	double denom = 1.0 / mag;
		
	return new Vector(this->getX() * denom, this->getY() * denom, this->getZ() * denom);
	
}

Vector* Vector::mult(double scalar){
	
	double x = this->getX() * scalar;
	double y = this->getY() * scalar;
	double z = this->getZ() * scalar;
	
	return new Vector(x, y, z);
	
}

Vector* Vector::div(double scalar){

	double denom = 1 / scalar;
	double x = this->getX() * denom;
	double y = this->getY() * denom;
	double z = this->getZ() * denom;

	return new Vector(x, y, z);
}

Vector* Vector::add(Vector* other){
	
	double x = this->getX() + other->getX();
	double y = this->getY() + other->getY();
	double z = this->getZ() + other->getZ();
	
	return new Vector(x, y, z);
	
}

Vector* Vector::sub(Vector* other){

	double x = this->getX() - other->getX();
	double y = this->getY() - other->getY();
	double z = this->getZ() - other->getZ();
	
	return new Vector(x, y, z);

}

double Vector::getLength(){
	return sqrt((getX() * getX()) + (getY() * getY()) + (getZ() * getZ()));
}