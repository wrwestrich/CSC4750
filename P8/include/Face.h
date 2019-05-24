#if !defined FACE_H
#define FACE_H

#include "Pixel.h"
#include "Vertex.h"
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
      void render(Pixel*, Matrix*);
      void renderDDA(Pixel*, Vertex*, Vertex*);
      void renderBresenham(Pixel*, Vertex*, Vertex*);
      void displayFace();
};

#endif
