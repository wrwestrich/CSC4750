#if !defined (NODE_H)
#define NODE_H

#include "Pixel.h"
#include "DeleteObject.h"
#include "Matrix.h"
using CSC1310::Matrix;
#include "Light.h"
#include "Vertex.h"

class Node : public DeleteObject
{
   private:

   protected:
      Matrix* transform;

   public:
      Node();
      virtual ~Node();
      virtual void render(Pixel*, Matrix*, Matrix*, Light*, Color*, Vertex*, double, double) = 0;
};

#endif
