#if !defined FACE_H
#define FACE_H

#include "Pixel.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Light.h"
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
      void render(Pixel*, Matrix*, Matrix*, Matrix*, Color*, Light*, Color*, Vertex*, double, double);
      void renderFace(Pixel*, Matrix*, Matrix*, Matrix*, Vertex*, Vertex*, Vertex*, Color*, Light*, Color*, Vertex*, double, double);
      Vector* calculateShading(Vertex*, Matrix*, Color*, Light*, Color*, Vertex*, double, double);
      void renderDDA(Pixel*, Vertex*, Vertex*);
      void renderBresenham(Pixel*, Vertex*, Vertex*);
      void displayFace();
      Vector* getNormal(Matrix*);
};

#endif
