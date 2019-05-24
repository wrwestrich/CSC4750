//InstanceObject.h
#ifndef INSTANCEOBJECT_H
#define INSTANCEOBJECT_H

#include "Node.h"
#include "Matrix.h"
#include "Pixel.h"
#include "BasicObject.h"

class InstanceObject : public Node{
	
	private:
		BasicObject* obj;
	
	
	public:
		InstanceObject(BasicObject*);
		virtual ~InstanceObject();
		void buildTransform(Matrix*);
		void render(Pixel*, Matrix*);
	
};
#endif