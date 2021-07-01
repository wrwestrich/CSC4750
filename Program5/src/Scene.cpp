//Scene.cpp

#include "Scene.h"

using CSC1310::ListArrayIterator;

Scene::Scene(Matrix* other){
	
	transform = other;
	instances = new ListArray<Node>();
	
}

Scene::~Scene(){
	
	ListArrayIterator<Node>* instIter = instances->iterator();

   while (instIter->hasNext())
   {
      Node* instance = instIter->next();
      delete instance;
	  //instance->removeRef();
   }

   delete instIter;
   delete instances;
	
}

void Scene::addInstance(Node* obj){
	
	instances->add(obj);
	//obj->addRef();
	
}

void Scene::render(Pixel* pix){

    Matrix* zBuffer = new Matrix(pix->getHeight(), pix->getWidth());

    for(int i = 1; i <= pix->getHeight(); ++i){
        for(int j = 1; j <= pix->getWidth(); ++j){
            zBuffer->setElement(i, j, -1);
        }
    }

	ListArrayIterator<Node>* instIter = instances->iterator();

   while (instIter->hasNext())
   {
      Node* instance = instIter->next();
      instance->render(pix, zBuffer, transform);
   }

   delete instIter;
   delete zBuffer;

}
