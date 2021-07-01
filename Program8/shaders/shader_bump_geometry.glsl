
//values from vertex shader
varying vec3 v_lightVec; 
varying vec3 v_eyeVec;
varying vec2 v_texCoord;

//values to be passed to fragment shader
varying vec3 g_lightVec; 
varying vec3 g_eyeVec;
varying vec2 g_texCoord;

void main(){

   // get the s,t coordinates of each vertex
   float s1 = gl_TexCoordIn[0][0].s;  //first index is triangle number
   float s2 = gl_TexCoordIn[1][0].s;  //second index is texture coordinate number
   float s3 = gl_TexCoordIn[2][0].s;

   float t1 = gl_TexCoordIn[0][0].t;
   float t2 = gl_TexCoordIn[1][0].t;
   float t3 = gl_TexCoordIn[2][0].t;
   
   //iterate through each vertex
   for(int i = 0; i < gl_VerticesIn; i++){

      gl_Position = gl_PositionIn[i];
      gl_TexCoord[0] = gl_TexCoordIn[i][0];  //copy over the texture coords

      //texture correction (wedge of death)
      //a better soln is to check the quadrant of the vertices (look for quad 4/quad 1 overlap)
      if((s1 > 0.9 || s2 > 0.9 || s3 > 0.9) && gl_TexCoord[0].s < 0.1){

         gl_TexCoord[0].s += 1.0;
         
      }

      EmitVertex();
   }

   EndPrimitive();

   //pass along values to fragment shader
   g_lightVec = v_lightVec;
   g_eyeVec   = v_eyeVec;
   g_texCoord = v_texCoord;
}
