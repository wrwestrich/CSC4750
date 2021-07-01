//InstanceObject.cpp

#include "InstanceObject.h"
#include <iostream>

InstanceObject::InstanceObject(BasicObject* other){

    mat = NULL;

	tex = NULL;

	textureColors = NULL;

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

InstanceObject::InstanceObject(BasicObject* other, char* textureFile, int texWidth, int texHight){

	mat = NULL;

	tex = new Texture(textureFile, texWidth, texHight);

	textureColors = NULL;

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
    delete mat;
	/*if(tex)*/ delete tex;
	/*if(textureColors)*/ delete [] textureColors;
	
}

void InstanceObject::setMaterial(Color* material){
    
    mat = material;

}

void InstanceObject::buildTransform(Matrix* foo){
	
	Matrix* temp = foo->multiply(transform);
	delete transform;
	transform = temp;
	
}

unsigned char* InstanceObject::readTexture(Texture* tex){
	int width = tex->getWidth();
   	int height = tex->getHeight();
   	int numColors = width*height*3;
   	char* textureFile = tex->getFileName();

   	unsigned char* data = new unsigned char[numColors];  

   	std::ifstream inFile(textureFile, std::ios::binary | std::ios::in);   
	inFile.seekg(0, inFile.beg);
   	inFile.read(reinterpret_cast<char*>(data), numColors);
   	inFile.close();

   	return data;
}

void InstanceObject::render(Pixel* pix, Matrix* zBuffer, Matrix* W, Light* lightPoint, Color* ambLight, Vertex* E, double attn, double shine){
	
	//Matrix* temp = W->multiply(transform);
	textureColors = readTexture(tex);
	obj->render(pix, zBuffer, W, transform, mat, lightPoint, ambLight, E, attn, shine, tex, textureColors);
	
	//delete temp;
	
}
