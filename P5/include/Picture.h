#if !defined (PICTURE_H)
#define PICTURE_H

#include "Pixel.h"
#include "BasicObject.h"
#include "InstanceObject.h"
#include "TransformNode.h"
#include "Scene.h"
#include "Vector.h"
#include "Vertex.h"

class Picture
{
   public:
      static void render(Pixel*);
      static BasicObject* readObject(const char*);

   private:
};

#endif
