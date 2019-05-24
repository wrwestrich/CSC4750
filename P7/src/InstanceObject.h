//InstanceObject.h
#ifndef INSTANCEOBJECT_H
#define INSTANCEOBJECT_H

#include "Node.h"
#include "Matrix.h"
#include "Pixel.h"
#include "BasicObject.h"
#include "Color.h"
#include "Light.h"
#include "Texture.h"

#include <fstream>

class InstanceObject : public Node{
	
	private:
		BasicObject* obj;
        Color* mat;
		Texture* tex;
		unsigned char* textureColors;
	
	
	public:
		InstanceObject(BasicObject*);
		InstanceObject(BasicObject*, char*, int, int);
		virtual ~InstanceObject();
        void setMaterial(Color*);
		void buildTransform(Matrix*);
		unsigned char* readTexture(Texture*);
		void render(Pixel*, Matrix*, Matrix*, Light*, Color*, Vertex*, double, double);
	
};
#endif
