//InstanceObject.h
#ifndef INSTANCEOBJECT_H
#define INSTANCEOBJECT_H

#include "Node.h"
#include "Matrix.h"
#include "Pixel.h"
#include "BasicObject.h"
#include "Color.h"

class InstanceObject : public Node{
	
	private:
		BasicObject* obj;
        Color* mat;
	
	
	public:
		InstanceObject(BasicObject*);
		virtual ~InstanceObject();
        void setMaterial(Color*);
		void buildTransform(Matrix*);
		void render(Pixel*, Matrix*, Matrix*);
	
};
#endif
