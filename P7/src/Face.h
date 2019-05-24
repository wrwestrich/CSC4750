#if !defined FACE_H
#define FACE_H

#include "Pixel.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Light.h"
#include "ListArray.h"
#include "Texture.h"

#include <vector>

using CSC1310::ListArray;

class Face
{
   private:
      ListArray<Vertex>* vertices;
      int size;
      std::vector<TextureCoords> textureCoords;

   public:
      Face();
      ~Face();
      void addVertex(Vertex*);
      Vertex* getVertex(int);
      void addTextureCoords(double, double);
      void render(Pixel*, Matrix*, Matrix*, Matrix*, Color*, Light*, Color*, Vertex*, double, double, Texture*, unsigned char*);
      void renderFace(Pixel*, Matrix*, Matrix*, Matrix*, Vertex*, Vertex*, Vertex*, Color*, Light*, Color*, Vertex*, double, double, Texture*, unsigned char*);
      Vector* calculateShading(Vertex*, Matrix*, Color*, Light*, Color*, Vertex*, double, double);
      double calculateLighting(Vertex*, Matrix*, Light*);
      void renderDDA(Pixel*, Vertex*, Vertex*);
      void renderBresenham(Pixel*, Vertex*, Vertex*);
      void displayFace();
      Vector* getNormal(Matrix*);
};

#endif
