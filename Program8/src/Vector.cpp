#include "Vector.h"
#include <Math.h>

Vector::Vector(double x, double y, double z)
{
   vector = new Matrix(4, 1);
   vector->setElement(1, 1, x);
   vector->setElement(2, 1, y);
   vector->setElement(3, 1, z);
   vector->setElement(4, 1, 0.0);  //4th coordinate 0 for vectors
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

Vector* Vector::cross(Vector* cross)
{
   Vector* result = new Vector(0, 0, 0);

   double temp = getY()*cross->getZ() - getZ()*cross->getY();
   result->setX(temp);
   temp = getZ()*cross->getX() - getX()*cross->getZ();
   result->setY(temp);
   temp = getX()*cross->getY() - getY()*cross->getX();
   result->setZ(temp);

   return result;
}

double Vector::dot(Vector* dot)
{
   double result;
  
   result = getX()*dot->getX();
   result += getY()*dot->getY();
   result += getZ()*dot->getZ();

   return result;
}

Vector* Vector::normalize()
{
   Vector* result = new Vector(0, 0, 0);
   double sum;

   sum = getX()*getX() + getY()*getY() + getZ()*getZ();
   sum = sqrt(1.0/sum);
   result->setX(getX()*sum);
   result->setY(getY()*sum);
   result->setZ(getZ()*sum);

   return result;
}

Vector* Vector::multiply(Matrix* matrix)
{
   Vector* result = new Vector(0, 0, 0);

   if (matrix->getNumRows() == 4 && matrix->getNumCols() == 4)
   {
      Matrix* temp = matrix->multiply(vector);
      result->setX(temp->getElement(1, 1));
      result->setY(temp->getElement(2, 1));
      result->setZ(temp->getElement(3, 1));
      delete temp;
   }

   return result;
}

void Vector::printVector()
{
   vector->displayMatrix();
}
