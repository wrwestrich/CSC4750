#include "Picture.h"
#include "Color.h"
#include "AffineTransforms.h"

#include "Tokens.h"
using CSC1310::Tokens;
#include "ReadFile.h"
using CSC1310::ReadFile;

#include <math.h>
#include <iostream>
using namespace std;

void readTransform(ReadFile* file, double& x, double& y, double& z){
	
	//Go past the transform type
	String* line = file->readLine();
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
	
}

void buildInstance(InstanceObject* instance, ReadFile* file){
	
	double x, y, z;
	
	readTransform(file, x, y, z);
	Matrix* scale = AffineTransforms::scale(x, y, z);
	
	readTransform(file, x, y, z);
	Matrix* rotate = AffineTransforms::rotate(x, y, z);
	
	readTransform(file, x, y, z);
	Matrix* translate = AffineTransforms::translate(x, y, z);

    readTransform(file, x, y, z);
    Color* mat = new Color(x, y, z);
	
	instance->buildTransform(scale);
	instance->buildTransform(rotate);
	instance->buildTransform(translate);
    instance->setMaterial(mat);
	
	delete scale;
	delete rotate;
	delete translate;
	delete file;
	
}

void Picture::render(Pixel* pix)
{
//while(true)
//{
	const char* file_name = "../data/sphere_texture.txt";
	//const char* file_name = "../data/cube_texture.txt";

	BasicObject* sphere = readObject(file_name);
	//BasicObject* cube = readObject(file_name);

	//obtaining the window transform
	int width = pix->getWidth();  //the dimensions of the panel on which the drawing will occur
	int height = pix->getHeight();
	double aspect_ratio = (double) height/width;

	ReadFile* file = new ReadFile("../data/fov.txt");
	
	//Skip label line
	String* line = file->readLine();
	delete line;
	
	line = file->readLine();
	double angle = line->a_to_f();		//field of view specified in degrees
	angle = 3.1415927*angle/180.0;  	//get the angle in radians
	delete line;
	
	//Skip label line
	line = file->readLine();
	delete line;
	
	line = file->readLine();
	double zmax = line->a_to_f();
	delete line;
	
	//Skip label line
	line = file->readLine();
	delete line;
	
	line = file->readLine();
	double zmin = line->a_to_f();
	delete line;
	
	delete file;

	double w = 2*tan(angle/2);  //the width of the camera is determined by its fov
	double h = w*aspect_ratio;  //the height of the camera is determined by the width and the aspect ratio of the viewport

	//Build components needed for camera transform
	file = new ReadFile("../data/camera.txt");
	double x, y, z;
	readTransform(file, x, y, z);
	Vertex* E = new Vertex(x, y, z);
	
	readTransform(file, x, y, z);
	Vertex* A = new Vertex(x, -y, z);
	
	readTransform(file, x, y, z);
	Vector* v_up = new Vector(x, y, z);
	
	delete file;
	
	Matrix* camera = AffineTransforms::camera(E, A, v_up);
	Matrix* aspect = AffineTransforms::scale(2.0/w, 2.0/h, 1.0);  //aspect ratio correction transformation
	//the windowing transform takes width and height in pixels and converts from world coordinates to a coordinate system with (0,0) in the upper left and (width,height) in the lower right
	Matrix* normal = AffineTransforms::normal(zmin, zmax);
	Matrix* window = AffineTransforms::window(width, height);
	
	//Multiply all the transform matrices
	Matrix* temp1 = aspect->multiply(camera);
	Matrix* temp2 = normal->multiply(temp1);
	Matrix* transform = window->multiply(temp2);
	
	Scene* scene = new Scene(transform, E);
	
	InstanceObject* instance = new InstanceObject(sphere, "../data/MoonMap.raw", 800, 400);
	//InstanceObject* instance = new InstanceObject(cube, "../data/TTU.raw", 128, 128);
	
	buildInstance(instance, new ReadFile("../data/trs.txt"));
	
	scene->addInstance(instance);
	
	scene->render(pix);
	
	delete E;
	delete A;
	delete v_up;
	delete temp1;
	delete temp2;
	delete camera;
	delete aspect;
	delete normal;
	delete window;
	delete transform;
	delete scene;
	
}

//}

int getFaceIndex(String* face_indices)
{

	Tokens* tokens  = new Tokens(face_indices, '/');
	int num_tokens = tokens->getNumTokens();

   String* face_index = tokens->getToken(0);
   int index = face_index->a_to_i();

   //delete all of the tokens, used and unused
   for (int i = 0; i < num_tokens; i++)
   {
      String* temp = tokens->getToken(i);
      delete temp;
   }
   
   delete tokens;
   return index;
}

BasicObject* Picture::readObject(const char* file_name)
{
   BasicObject* obj = new BasicObject();
   ReadFile* rf = new ReadFile(file_name); //assumed to be a read if a delimiter is specified

   ListArray<Vertex> vertices;
   double x, y, z;
	 int faceCount = 1;
   String* v = new String("v");
   String* f = new String("f");
	 String* vt = new String("vt");

   String* line = rf->readLine();
	
   while (!rf->eof())
   {
      Tokens* tokens = new Tokens(line, ' ');
	  int num_tokens = tokens->getNumTokens();
      String* token = tokens->getToken(0);

      //all vertices are held in the vertices list so that the faces can be created
      if (token->compare(v) == 0)  //vertices
      {
         delete token;

         token = tokens->getToken(1);
         x = token->a_to_f();
         delete token;

         token = tokens->getToken(2);
         y = token->a_to_f();
         delete token;
		 
         token = tokens->getToken(3);
         z = token->a_to_f();
         delete token;

         Vertex* vertex = new Vertex(x, y, z);
         vertices.add(vertex);
         obj->addVertex(vertex);
      }

      else if (token->compare(f) == 0)  //face definition
      {
         delete token;

         String* face_indices = tokens->getToken(1);
         int index1 = getFaceIndex(face_indices);
         delete face_indices;
		 
         face_indices = tokens->getToken(2);
         int index2 = getFaceIndex(face_indices);
         delete face_indices;
		 
         face_indices = tokens->getToken(3);
         int index3 = getFaceIndex(face_indices);
         delete face_indices;

         Face* face = new Face();

         Vertex* vertex1 = vertices.get(index1);
         Vertex* vertex2 = vertices.get(index2);
         Vertex* vertex3 = vertices.get(index3);

         face->addVertex(vertex1);
         face->addVertex(vertex2);
         face->addVertex(vertex3);

				 //vertex1->addFace(face);
				 //vertex2->addFace(face);
				 //vertex3->addFace(face);

         obj->addFace(face);
      }
			else if (token->compare(vt) == 0){
				 delete token;

         token = tokens->getToken(1);
         double s1 = token->a_to_f();
         delete token;

				 token = tokens->getToken(2);
         double t1 = token->a_to_f();
         delete token;

				 token = tokens->getToken(3);
         double s2 = token->a_to_f();
         delete token;

				 token = tokens->getToken(4);
         double t2 = token->a_to_f();
         delete token;

				 token = tokens->getToken(5);
         double s3 = token->a_to_f();
         delete token;

				 token = tokens->getToken(6);
         double t3 = token->a_to_f();
         delete token;

				 //cout << s1 << ", " << t1 << ": " << s2 << ", " << t2 << ": " << s3 << ", " << t3 << endl;

				 obj->getFace(faceCount)->addTextureCoords(s1, t1);
				 obj->getFace(faceCount)->addTextureCoords(s2, t2);
				 obj->getFace(faceCount++)->addTextureCoords(s3, t3);
			}

      //still need to delete the tokens even if the line is completely disregarded
      else  
      {
			for (int i = 0; i < num_tokens; i++)
			{
				String* temp = tokens->getToken(i);
				delete temp;
			}
      }

	  delete line;
      delete tokens;
	  line = rf->readLine();
   }

   delete line;
   delete v;
   delete f;
   delete rf;
	 delete vt;
   
   return obj;
}

//Old code in case I need to use it later
/*
	InstanceObject* instance1 = new InstanceObject(sphere);
	InstanceObject* instance2 = new InstanceObject(sphere);
	
	ReadFile* file1 = new ReadFile("trs1.txt");
	ReadFile* file2 = new ReadFile("trs2.txt");
	
	//Read in first transform from file and build first instance
	buildInstance(instance1, file1);
	
	scene->addInstance(instance1);
	
	delete file1;
	
	//Read in second transform from file and build second instance
	buildInstance(instance2, file2);
	
	scene->addInstance(instance2);
	
	delete file2;	
	
	//Render the scene
	scene->render(pix);
	*/
	
	/*
	Matrix* scale;
	Matrix* translate;
	Matrix* rotate;
	
	// Create instances
	scale = AffineTransforms::scale(.2,1,.2);
	InstanceObject* upperArm = new InstanceObject(cube);
	upperArm->buildTransform(scale);
	delete scale;
	
	scale = AffineTransforms::scale(.2,2,.2);
	InstanceObject* lowerArm = new InstanceObject(cube);
	lowerArm->buildTransform(scale);
	delete scale;
	
	InstanceObject* base = new InstanceObject(cylinder);
	
	//Build upper arm transform
	TransformNode* upperTransform = new TransformNode();
	
	translate = AffineTransforms::translate(0,1,0);
	upperTransform->buildTransform(translate);
	delete translate;
	
	rotate = AffineTransforms::rotateZ(90);
	upperTransform->buildTransform(rotate);
	delete rotate;
	
	translate = AffineTransforms::translate(0,2,0);
	upperTransform->buildTransform(translate);
	delete translate;
	
	//Add upper arm as transform's child
	upperTransform->addChild(upperArm);
	
	//Build lower arm transform
	TransformNode* lowerTransform = new TransformNode();
	
	translate = AffineTransforms::translate(0,2,0);
	lowerTransform->buildTransform(translate);
	delete translate;
	
	rotate = AffineTransforms::rotateZ(-20);
	lowerTransform->buildTransform(rotate);
	delete rotate;
	
	translate = AffineTransforms::translate(0,1,0);
	lowerTransform->buildTransform(translate);
	delete translate;
	
	//Add children of lower arm transform
	lowerTransform->addChild(upperTransform);
	lowerTransform->addChild(lowerArm);
	
	//Build base transform
	TransformNode* baseTransform = new TransformNode();
	
	rotate = AffineTransforms::rotateY(30);
	baseTransform->buildTransform(rotate);
	delete rotate;
	
	translate = AffineTransforms::translate(0,-2,0);
	baseTransform->buildTransform(translate);
	delete translate;
	
	//Add children of base transform
	baseTransform->addChild(lowerTransform);
	baseTransform->addChild(base);
	
	//Build scene objects
	TransformNode* arm1 = new TransformNode();
	
	scale = AffineTransforms::scale(.2,.2,.2);
	arm1->buildTransform(scale);
	delete scale;
	
	translate = AffineTransforms::translate(0,0,-3);
	arm1->buildTransform(translate);
	delete translate;
	
	TransformNode* arm2 = new TransformNode();
	
	scale = AffineTransforms::scale(.2,.2,.2);
	arm2->buildTransform(scale);
	delete scale;
	
	rotate = AffineTransforms::rotateX(45);
	arm2->buildTransform(rotate);
	delete rotate;
	
	translate = AffineTransforms::translate(-3,0.5,0);
	arm2->buildTransform(translate);
	delete translate;
	
	scale = AffineTransforms::scale(.2,.2,.2);
	arm2->buildTransform(scale);
	delete scale;
	
	//Add base transform as a child to arms
	arm1->addChild(baseTransform);
	arm2->addChild(baseTransform);
	
	//Add instances to scene
	scene->addInstance(arm1);
	scene->addInstance(arm2);
	
	scene->render(pix);
	
	delete aspect;
	delete window;
	delete transform;
	//delete cube;
	//delete cylinder;
	//delete sphere;
	delete scene;
	*/
