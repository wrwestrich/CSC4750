//TransformNode.cpp

#include "TransformNode.h"
#include <iostream>
using std::cout;
using std::endl;

TransformNode::TransformNode(){
		
	children = new ListArray<Node>();
		
	transform->setElement(1,1,1);
	transform->setElement(1,2,0);
	transform->setElement(1,3,0);
	transform->setElement(1,4,0);

	transform->setElement(2,1,0);
	transform->setElement(2,2,1);
	transform->setElement(2,3,0);
	transform->setElement(2,4,0);
	
	transform->setElement(3,1,0);
	transform->setElement(3,2,0);
	transform->setElement(3,3,1);
	transform->setElement(3,4,0);
	
	transform->setElement(4,1,0);
	transform->setElement(4,2,0);
	transform->setElement(4,3,0);
	transform->setElement(4,4,1);
	
}

TransformNode::~TransformNode(){
	
	ListArrayIterator<Node>* nodeIter = children->iterator();

	while (nodeIter->hasNext())
	{
		Node* node = nodeIter->next();
		node->removeRef();
		//delete node;
	}

	delete nodeIter;
	delete children;
	
}

void TransformNode::buildTransform(Matrix* foo){
	
	Matrix* temp = foo->multiply(transform);
	delete transform;
	transform = temp;
		
}

void TransformNode::addChild(Node* child){
	
	children->add(child);
	child->addRef();
	
}

void TransformNode::render(Pixel* pix, Matrix* W){
	
	Matrix* temp = W->multiply(transform);
	ListArrayIterator<Node>* nodeIter = children->iterator();

	while (nodeIter->hasNext())
	{
		Node* node = nodeIter->next();
		node->render(pix, temp);
	}

	delete nodeIter;	
	delete temp;
	
}