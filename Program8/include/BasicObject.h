#if !defined BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include "Face.h"
#include "DeleteObject.h"

class BasicObject : public DeleteObject
{
   private:
      ListArray<Face>* faces;
      ListArray<Vertex>* vertices;
      int size;

   public:
      BasicObject();
      virtual ~BasicObject();
      void addFace(Face*);
      void addVertex(Vertex*);
      Face* getFace(int);
      void render(Pixel*, Matrix*);
};

#endif
