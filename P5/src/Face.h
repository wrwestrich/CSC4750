#if !defined FACE_H
#define FACE_H

#include "Pixel.h"
#include "Vertex.h"
#include "Matrix.h"
#include "ListArray.h"
using CSC1310::ListArray;

class Face
{
   private:
      ListArray<Vertex>* vertices;
      int size;

   public:
      Face();
      ~Face();
      void addVertex(Vertex*);
      Vertex* getVertex(int);
      void render(Pixel*, Matrix*, Matrix*, Color*);
      void renderFace(Pixel*, Matrix*, Vertex*, Vertex*, Vertex*);
      void renderDDA(Pixel*, Vertex*, Vertex*);
      void renderBresenham(Pixel*, Vertex*, Vertex*);
      void displayFace();
};

#endif
