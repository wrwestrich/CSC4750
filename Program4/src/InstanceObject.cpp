//InstanceObject.cpp

#include "InstanceObject.h"

InstanceObject::InstanceObject(BasicObject* other){
	
	obj = other;
	obj->addRef();
		
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

InstanceObject::~InstanceObject(){
	
	obj->removeRef();
	
}

void InstanceObject::buildTransform(Matrix* foo){
	
	Matrix* temp = foo->multiply(transform);
	delete transform;
	transform = temp;
	
}

void InstanceObject::render(Pixel* pix, Matrix* W){
	
	Matrix* temp = W->multiply(transform);
	obj->render(pix, temp);
	
	delete temp;
	
}