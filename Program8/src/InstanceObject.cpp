#include "InstanceObject.h"

#ifdef __MACH__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
using namespace std;

InstanceObject::InstanceObject(BasicObject* bo) : Node()
{
   obj = bo;
   obj->addRef();
   diffuse = new Color(0.3, 0.3, 1.0);
   shininess = 0;
   color_texture = NULL;
   bump_texture = NULL;
}

InstanceObject::~InstanceObject()
{
   obj->removeRef();  //several ios can use the same bo, so delete is tricky
   delete diffuse;
}

void InstanceObject::setDiffuseMaterial(Color* mat)
{
   Color* temp = diffuse;
   diffuse = mat;
   delete temp;

   if (color_texture != NULL)
   {
      delete color_texture;
   }
}

void InstanceObject::setColorTexture(Texture* tex)
{
   if (color_texture == NULL)
   {
      color_texture = tex;
   }
   else
   {
      delete color_texture;
      color_texture = tex;
   }
}

void InstanceObject::setBumpTexture(Texture* tex)
{
   if (bump_texture == NULL)
   {
      bump_texture = tex;
   }
   else
   {
      delete bump_texture;
      bump_texture = tex;
   }
}

void InstanceObject::setShininess(double shine)
{
   shininess = shine;
}

void InstanceObject::buildTransform(Matrix* matrix)
{
   //multiple calls to this method will achieve the proper concatenation (later matrices are on the left)
   Matrix* temp = matrix->multiply(transform);
   delete transform;
   delete matrix;
   transform = temp;
}

unsigned char* InstanceObject::readTexture(Texture* tex)
{
   int width = tex->getWidth();
   int height = tex->getHeight();
   int numColors = width*height*3;
   char* textureFile = tex->getFileName();

   unsigned char* textureColors = new unsigned char[numColors];  
   ifstream infile(textureFile, ios::binary);   
   infile.read((char*)textureColors, numColors);
   infile.close();

   return textureColors;
}

void InstanceObject::render(Matrix* laterTransform)
{
   Matrix* updatedMatrix = laterTransform->multiply(transform);
   GLfloat* diffuse0 = new GLfloat[4];

   if (color_texture != NULL && bump_texture != NULL)
   {
      unsigned char* textureColors = readTexture(color_texture);
      int w = color_texture->getWidth();  //power of two
      int h = color_texture->getHeight(); //power of two

      unsigned char* bumpColors = readTexture(bump_texture);
      int w_bump = bump_texture->getWidth();  //power of two
      int h_bump = bump_texture->getHeight(); //power of two

      //need GPU memory to hold two texture map
      GLuint* texNum = new GLuint[2];
      glGenTextures(2, texNum);

      //glClientActiveTexture(GL_TEXTURE0);
	   //glDisableClientState(GL_TEXTURE_COORD_ARRAY);

      glEnable(GL_TEXTURE_2D);  //could use a 1D, 2D, or 3D texture unit
      glActiveTexture(GL_TEXTURE0); //must be the same as the sampler2D variable assignment 

      //creates a texture object
      glBindTexture(GL_TEXTURE_2D, texNum[0]);  
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, textureColors);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

      //Create bump texture
      glActiveTexture(GL_TEXTURE1); //must be the same as the sampler2D variable assignment 

      //creates a texture object
      glBindTexture(GL_TEXTURE_2D, texNum[1]);  
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w_bump, h_bump, 0, GL_RGB, GL_UNSIGNED_BYTE, bumpColors);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

      diffuse0[0] = 1.0;
      diffuse0[1] = 1.0;
      diffuse0[2] = 1.0;
      diffuse0[3] = 1.0;
   }
   else
   {
      glDisable(GL_TEXTURE_2D);
      diffuse0[0] = diffuse->getRed();
      diffuse0[1] = diffuse->getGreen();
      diffuse0[2] = diffuse->getBlue();
      diffuse0[3] = 1.0;
   }

   glPushMatrix();
   glPushAttrib(GL_CURRENT_BIT);  //saves OpenGL state information

   //get the instance transform and apply it
   //requires a column major matrix for OpenGL
   const float* updated_array = updatedMatrix->toArrayColumnMajor();
   glMultMatrixf(updated_array);

   glActiveTexture(GL_TEXTURE0);
  
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse0);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   obj->render();

   glPopAttrib();  //restores OpenGL state information
   glPopMatrix();

   delete[] updated_array;
   delete updatedMatrix;
   delete[] diffuse0;
}
