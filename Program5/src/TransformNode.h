//TransformNode.h
#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include "Node.h"
#include "Matrix.h"
#include "Pixel.h"
#include "BasicObject.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

class TransformNode : public Node{
	
	private:
		ListArray<Node>* children;
	
	public:
		TransformNode();
		virtual ~TransformNode();
		void buildTransform(Matrix*);
		void addChild(Node*);
		void render(Pixel*, Matrix*, Matrix*);
	
};
#endif
