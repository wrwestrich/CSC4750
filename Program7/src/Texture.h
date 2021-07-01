#if !defined (TEXTURE_H)
#define TEXTURE_H

//Struct for texture coords
struct TextureCoords{
   double s;
   double t;

   TextureCoords(double _s, double _t) : s(_s), t(_t){}
};

class Texture
{
   private:
      char* textureFile;
      int width;
      int height;

   public:
      Texture(char* texFile, int w, int h);
      virtual ~Texture();
      char* getFileName();
      int getWidth();
      int getHeight();
};

#endif
