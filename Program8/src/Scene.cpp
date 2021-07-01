#include "Scene.h"

#ifdef __MACH__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;
#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

Scene::Scene()
{
   transformNodes = new ListArray<TransformNode>();
   light = new Light();
   //light->setLocation(new Vertex(-2, -5, 4));
   light->setLocation(new Vertex(3, 3, 3));
   light->setColor(new Color(1, 1, 1));
   eyepoint = new Vertex(0, 0, 4);
   atpoint = new Vertex(0, 0, 0);
   ambient = new Color(.03, .03, .03);
   linearAttenuation = 0.2;
   fovx = 45.0;
   zmax = -2.0;
   zmin = -10.0;
}

Scene::~Scene()
{
   //clean up all of the basic object heap-allocated memory
   ListArrayIterator<TransformNode>* ioIter = transformNodes->iterator();
   while (ioIter->hasNext())
   {
      TransformNode* tn = ioIter->next();
      tn->removeRef();
   }

   delete ioIter;
   delete transformNodes;

   delete light;
   delete eyepoint;
   delete atpoint;
   delete ambient;
}

void Scene::addTransformNode(TransformNode* tn)
{
   transformNodes->add(tn);
   tn->addRef();
}

void Scene::render(int w, int h)
{
   //glShadeModel(GL_FLAT);

   glClear(GL_DEPTH_BUFFER_BIT);  //clear the color buffer
   glClear(GL_COLOR_BUFFER_BIT);  //clear the color buffer

   glMatrixMode(GL_PROJECTION);  //set up the projection matrix
   
   glLoadIdentity();
   float ratio = ((double) h)/w;  //height/width

   //glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -100, 100);  //assumes all vertices are in the range -1 to 1 in x and y (accepts nearly any z)
   //gluPerspective(fovy, ratio, near, far);  //uses fovy, not what I want

   //manually build the perspective transform as OpenGL uses fovy
   Matrix* perspective = AffineTransforms::perspectiveNorm(fovx, ratio, zmax, zmin);
   const float* perspective_array = perspective->toArrayColumnMajor();
   glMultMatrixf(perspective_array);
   delete perspective;

   //the main function for display
   glMatrixMode(GL_MODELVIEW);  //switch to modelview mode for display
   glLoadIdentity();
   gluLookAt(eyepoint->getX(), eyepoint->getY(), eyepoint->getZ(), atpoint->getX(), atpoint->getY(), atpoint->getZ(), 0, 1, 0); //eye, at, up

   //process the light source here for world coordinates
   Vertex* lightLoc = light->getLocation();
   GLfloat position0[] = {static_cast<GLfloat>(lightLoc->getX()), static_cast<GLfloat>(lightLoc->getY()), static_cast<GLfloat>(lightLoc->getZ()), 1.0};  //xyzw         
   GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};

   //use a global ambient light source that is a very dark red (using both light and material ambient components)
   GLfloat ambientLight[] = {static_cast<GLfloat>(ambient->getRed()), static_cast<GLfloat>(ambient->getGreen()), static_cast<GLfloat>(ambient->getBlue()), 1.0};  //a dark grey
   GLfloat ambientMat[] = {1.0, 0, 0, 1.0};  //usually set to just red

   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
   glLightfv(GL_LIGHT0, GL_POSITION, position0);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMat);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular0);

   Matrix* identity = Matrix::identity(4);
   
   //loop over all the Instance instances in the Scene and render them
   ListArrayIterator<TransformNode>* ioIter = transformNodes->iterator();
   while (ioIter->hasNext())
   {
      TransformNode* tn = ioIter->next();
      tn->render(identity);
   }

   delete identity;
   delete ioIter;
}
