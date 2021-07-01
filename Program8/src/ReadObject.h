#ifndef READ_OBJECT_H
#define READ_OBJECT_H

   int numVertices(const char* ptr);
   int numFaces(const char* ptr);
   float* getVertices(const char* ptr, int vcount);
   float* getNormals(const char* ptr, int vcount);
   unsigned short* getFaces(const char* ptr, int fcount);
   float* getColors(int numVertices, float r, float g, float b);
   float* getTextureCoords(const char* ptr, int vcount);
   char* getText(const char* file);

#endif
