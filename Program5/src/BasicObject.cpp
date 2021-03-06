#include "BasicObject.h"
using CSC1310::ListArrayIterator;

BasicObject::BasicObject()
{
   vertices = new ListArray<Vertex>();
   faces = new ListArray<Face>();
   size = 0;
}

BasicObject::~BasicObject()
{
   //clean up all of the basic object heap-allocated memory
   ListArrayIterator<Face>* faceIter = faces->iterator();
   while (faceIter->hasNext())
   {
      Face* face = faceIter->next();
      delete face;
   }

   ListArrayIterator<Vertex>* vertexIter = vertices->iterator();
   while(vertexIter->hasNext())
   {
      Vertex* vertex = vertexIter->next();
      delete vertex;  
   }

   delete faceIter;
   delete faces;
   delete vertexIter;
   delete vertices;
}

void BasicObject::addVertex(Vertex* vertex)
{
   vertices->add(vertex);
}

void BasicObject::addFace(Face* face)
{
   faces->add(size + 1, face);
   size++;
}

Face* BasicObject::getFace(int index)
{
   return faces->get(index);
}

void BasicObject::render(Pixel* pix, Matrix* zBuffer, Matrix* transform, Color* mat)
{
   ListArrayIterator<Face>* faceIter = faces->iterator();

   while (faceIter->hasNext())
   {
      Face* face = faceIter->next();
      face->render(pix, zBuffer, transform, mat);
   }

   delete faceIter;
}

