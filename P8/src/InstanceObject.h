#if !defined (INSTANCEOBJECT_H)
#define INSTANCEOBJECT_H

#include "Node.h"
#include "Texture.h"
#include "BasicObject.h"

class InstanceObject : public Node
{
   private:
      BasicObject* obj;
      Color* diffuse;
      Texture* color_texture;
      Texture* bump_texture;
      float shininess;

   public:
      InstanceObject(BasicObject* bo);
      virtual ~InstanceObject();
      void setDiffuseMaterial(Color* mat);
      void setShininess(double shine);
      void buildTransform(Matrix* matrix);
      void render(Matrix* laterTransform);
      void setColorTexture(Texture* tex);
      void setBumpTexture(Texture*);
      static unsigned char* readTexture(Texture* tex);
};

#endif
