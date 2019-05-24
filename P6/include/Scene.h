//Scene.h
#ifndef SCENE_H
#define SCENE_H

#include "InstanceObject.h"
#include "Matrix.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
#include "Pixel.h"

class Scene{
	
	private:
		ListArray<Node>* instances;
		Matrix* transform;
	
	public:
		Scene(Matrix*);
		~Scene();
		void addInstance(Node*);
		void render(Pixel*);
	
};
#endif