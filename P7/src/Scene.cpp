//Scene.cpp

#include "Scene.h"

using CSC1310::ListArrayIterator;

Scene::Scene(Matrix* other, Vertex* E){
	
	transform = other;
	instances = new ListArray<Node>();
    lightPoint = new Light();
    eyePoint = E;

    readLightValues();
	
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

   delete lightPoint;
   delete ambLight;
	
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
      instance->render(pix, zBuffer, transform, lightPoint, ambLight, eyePoint, attn, shine);
   }

   delete instIter;
   delete zBuffer;

}

void Scene::readLightValues(){

    ReadFile* file = new ReadFile("../data/shade.txt");

    //Read light point position
    String* line = file->readLine();
    delete line;

    line = file->readLine();
    double x = line->a_to_f();
    delete line;

    line = file->readLine();
    double y = line->a_to_f();
    delete line;

    line = file->readLine();
    double z = line->a_to_f();
    delete line;

    Vertex* loc = new Vertex(x, y, z);
    lightPoint->setLocation(loc);

    //Read ambient light color
    line = file->readLine();
    delete line;

    line = file->readLine();
    x = line->a_to_f();
    delete line;

    line = file->readLine();
    y = line->a_to_f();
    delete line;

    line = file->readLine();
    z = line->a_to_f();
    delete line;

    ambLight = new Color(x, y, z);

    //Read linear attenuation
    line = file->readLine();
    delete line;

    line = file->readLine();
    attn = line->a_to_f();
    delete line;

    //Read in shininess coeff
    line = file->readLine();
    delete line;

    line = file->readLine();
    shine = line->a_to_f();
    delete line;

    delete file;

}
