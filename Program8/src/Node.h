#if !defined (NODE_H)
#define NODE_H

#include "DeleteObject.h"
#include "Matrix.h"
using CSC1310::Matrix;

class Node : public DeleteObject
{
   private:

   protected:
      Matrix* transform;

   public:
      Node();
      virtual ~Node();
      virtual void render(Matrix* laterTransform) = 0;
};

#endif
