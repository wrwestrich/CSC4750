#include "Picture.h"
#include "Scene.h"

void Picture::render(int w, int h)
{
   //picture will not look exactly like in class programs
   //normals used are those from the text file

   const char* fileName = "../data/sphere_texture.txt";
   BasicObject* sphere = new BasicObject(fileName);

   InstanceObject* sphere1 = new InstanceObject(sphere);
   Color* d1 = new Color(0.3, 0.3, 0.9);
   sphere1->setDiffuseMaterial(d1);
   Texture* tex = new Texture("../data/MoonColor.raw", 512, 256);
   Texture* bump_tex = new Texture("../data/MoonNormal.raw", 512, 256);
   sphere1->setColorTexture(tex);
   sphere1->setBumpTexture(bump_tex);

   /*
   InstanceObject* sphere2 = new InstanceObject(sphere);
   Color* d2 = new Color(1.0, 0.0, 0.0);
   sphere2->setDiffuseMaterial(d2);
   */

   Scene* scene = new Scene();

   TransformNode* tn = new TransformNode();
   tn->buildTransform(AffineTransforms::scale(1, 1, 1));
   tn->buildTransform(AffineTransforms::rotateY(180));
   tn->buildTransform(AffineTransforms::translate(0, 0, 0));
   tn->addChild(sphere1);

   scene->addTransformNode(tn);

   /*
   tn = new TransformNode();
   tn->buildTransform(AffineTransforms::scale(.7, 1.3, .7));
   tn->buildTransform(AffineTransforms::rotateX(90));
   tn->buildTransform(AffineTransforms::rotateZ(290));
   tn->buildTransform(AffineTransforms::translate(-.75, .75, 0));
   tn->addChild(sphere2);

   scene->addTransformNode(tn);
   */

   scene->render(w, h);
   delete scene;
}
