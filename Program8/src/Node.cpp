#include "Node.h"

Node::Node() : DeleteObject()
{
   transform = Matrix::identity(4);
}

Node::~Node()
{
   delete transform;
}
