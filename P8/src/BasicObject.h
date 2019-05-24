#if !defined (BASICOBJECT_H)
#define BASICOBJECT_H

#include "DeleteObject.h"
#include "Color.h"

class BasicObject : public DeleteObject
{
   private:
      float* vertices;
      float* normals;
      unsigned short* indices;
      float* tex_coords;
      int indexCount;
      int vcount;

   public:
      BasicObject(const char* file);
      virtual ~BasicObject();
      void render();
};

#endif
