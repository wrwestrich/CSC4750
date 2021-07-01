
//from the vertex shader
varying vec3 g_lightVec;
varying vec3 g_eyeVec;
varying vec2 g_texCoord;

uniform sampler2D colorMap;
uniform sampler2D normalMap;

void main (void){
  
  //calculate the dristance from the light point
  float distSqr = dot(g_lightVec, g_lightVec);
  vec3 lVec = g_lightVec * inversesqrt(distSqr);

  vec3 vVec = normalize(g_eyeVec);
  
  //get the base texture and the bump from the textures
  vec4 base = texture2D(colorMap, g_texCoord);
  vec3 bump = normalize(texture2D(normalMap, g_texCoord).xyz * 2.0 - 1.0);

  //ambient color
  vec4 vAmbient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

  //diffuse
  float diffuse = max(dot(lVec, bump), 0.0);
  vec4 vDiffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * diffuse;  

  //specular
  float specular = pow(clamp(dot(reflect(-lVec, bump), vVec), 0.0, 1.0), gl_FrontMaterial.shininess);
  vec4 vSpecular = gl_LightSource[0].specular * gl_FrontMaterial.specular * specular;  
  
  //set the fragment final color
    gl_FragColor = vAmbient * base + vDiffuse * base; // + vSpecular;

}
