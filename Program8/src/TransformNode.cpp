#include "TransformNode.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

TransformNode::TransformNode() : Node()
{
   children = new ListArray<Node>();
   sze = 0;
}

TransformNode::~TransformNode()
{
   ListArrayIterator<Node>* iter = children->iterator();

   while (iter->hasNext())
   {
      Node* node = iter->next();
      node->removeRef();
   }

   delete children;
   delete iter;
}

void TransformNode::addChild(Node* child)
{
   children->add(sze + 1, child);
   child->addRef();
   sze++;
}

Node* TransformNode::getNode(int index)
{
   return children->get(index);
}

void TransformNode::buildTransform(Matrix* matrix)
{
   //in order to right multiply, concatentating transforms, use the Matrix multiply method thusly
   //multiple calls to this method will achieve the concatenation
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

void TransformNode::render(Matrix* laterTransform)
{
   //transform passed in from higher in the scene graph
   Matrix* updatedTransform = laterTransform->multiply(transform);

   ListArrayIterator<Node>* iter = children->iterator();
   while (iter->hasNext())
   {
      Node* node = iter->next();
      node->render(updatedTransform);
   }

   delete iter;
   delete updatedTransform;
}
