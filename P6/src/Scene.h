//Scene.h
#ifndef SCENE_H
#define SCENE_H

#include "InstanceObject.h"
#include "Matrix.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
#include "Pixel.h"
#include "Light.h"
#include "ReadFile.h"
#include "String_.h"
using CSC1310::ReadFile;
using CSC1310::String;

class Scene{
	
	private:
		ListArray<Node>* instances;
		Matrix* transform;

        Light* lightPoint;
        Color* ambLight;
        Vertex* eyePoint;
        double attn;
        double shine;

        void readLightValues();
	
	public:
		Scene(Matrix*, Vertex*);
		~Scene();
		void addInstance(Node*);
		void render(Pixel*);
	
};
#endif
