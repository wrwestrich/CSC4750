#include "Vertex.h"
#include "Face.h"
#include <iostream>

Vertex::Vertex(double x, double y, double z)
{
   color = new Color(1, 1, 1);
   vertex = new Matrix(4, 1);
   faces = new ListArray<Face>();

   vertex->setElement(1, 1, x);
   vertex->setElement(2, 1, y);
   vertex->setElement(3, 1, z);
   vertex->setElement(4, 1, 1.0);  //4th coordinate 1 for vertices
}

Vertex::~Vertex()
{
   delete vertex;
   delete color;
   delete faces;
}

void Vertex::setX(double x)
{
   vertex->setElement(1, 1, x);
}

void Vertex::setY(double y)
{
   vertex->setElement(2, 1, y);
}

void Vertex::setZ(double z)
{
   vertex->setElement(3, 1, z);
}

void Vertex::setH(double h)
{
   vertex->setElement(4, 1, h);
}

double Vertex::getX()
{
   return vertex->getElement(1, 1);
}

double Vertex::getY()
{
   return vertex->getElement(2, 1);
}

double Vertex::getZ()
{
   return vertex->getElement(3, 1);
}

double Vertex::getH()
{
   return vertex->getElement(4, 1);
}

void Vertex::setRed(double r)
{
   color->setRed(r);
}

void Vertex::setGreen(double g)
{
   color->setGreen(g);
}

void Vertex::setBlue(double b)
{
   color->setBlue(b);
}

double Vertex::getRed()
{
   return color->getRed();
}

double Vertex::getGreen()
{
   return color->getGreen();
}

double Vertex::getBlue()
{
   return color->getBlue();
}

Vertex* Vertex::multiply(Matrix* matrix)
{
   Vertex* result = new Vertex(0, 0, 0);  

   if (matrix->getNumRows() == 4 && matrix->getNumCols() == 4)
   {
      Matrix* temp = matrix->multiply(vertex);  //vertex is on the right
      result->setX(temp->getElement(1, 1));
      result->setY(temp->getElement(2, 1));
      result->setZ(temp->getElement(3, 1));
      result->setH(temp->getElement(4, 1));
      result->setRed(getRed());
      result->setGreen(getGreen());
      result->setBlue(getBlue());
      delete temp;
   }

   return result;
}

Vector* Vertex::sub(Vertex* other){
	
	double x = this->getX() - other->getX();
	double y = this->getY() - other->getY();
	double z = this->getZ() - other->getZ();
	
	return new Vector(x, y, z);
	
}

void Vertex::homogenize(){
	
	double denom = 1.0 / this->getH();
	double x = this->getX() * denom;
	double y = this->getY() * denom;
	double z = this->getZ() * denom;
	
	this->setX(x);
	this->setY(y);
	this->setZ(z);
	
}

//pseudo dot function for convenience
double Vertex::dot(Vector* other){
	
	return ((this->getX() * other->getX()) + (this->getY() * other->getY()) + (this->getZ() * other->getZ()));
	
}

void Vertex::addFace(Face* face){
   faces->add(face);
}

Vector* Vertex::averageNormal(Matrix* transform){
   Vector* normal = new Vector(0.0,0.0,0.0);
   
   int size = faces->size();
   for(int i = 0; i < size; ++i){
      Vector* temp = normal;
      normal = normal->add(faces->get(i+1)->getNormal(transform));
      delete temp;
   }
   Vector* temp = normal;
   normal = normal->div(size);
   delete temp;

   temp = normal;
   normal = normal->norm();
   delete temp;

   return normal;
}

void Vertex::displayVertex()
{
   vertex->displayMatrix();
}
