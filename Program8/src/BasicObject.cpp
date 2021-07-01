#include "BasicObject.h"
#include "ReadObject.h"

#ifdef __MACH__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

BasicObject::BasicObject(const char* file)
{
   vcount = numVertices(file);
   int fcount = numFaces(file);
   indexCount = fcount*3;

   vertices = getVertices(file, vcount);
   normals = getNormals(file, vcount);
   indices = getFaces(file, fcount);
   tex_coords = getTextureCoords(file, vcount);
}

BasicObject::~BasicObject()
{
   delete[] indices;
   delete[] vertices;
   delete[] normals;
   delete[] tex_coords;
}

void BasicObject::render()
{

   glClientActiveTexture(GL_TEXTURE0);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);

   glClientActiveTexture(GL_TEXTURE2);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, vertices);
   glNormalPointer(GL_FLOAT, 0, normals);
   glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);

   //render
   glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, indices);
}
