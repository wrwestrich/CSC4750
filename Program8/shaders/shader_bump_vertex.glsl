
varying vec3 v_lightVec; 
varying vec3 v_eyeVec;
varying vec2 v_texCoord;

attribute vec3 vTangent; 	 

void main(void){

	//set position and tex coord
	gl_Position = ftransform();
	v_texCoord = gl_MultiTexCoord2.st;
	
	//transform the normal of the vertex
	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * vTangent);
	vec3 b = cross(n, t);
	
	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 tmpVec = gl_LightSource[0].position.xyz - vVertex;

	v_lightVec.x = dot(tmpVec, t);
	v_lightVec.y = dot(tmpVec, b);
	v_lightVec.z = dot(tmpVec, n);

	tmpVec = -vVertex;
	v_eyeVec.x = dot(tmpVec, t);
	v_eyeVec.y = dot(tmpVec, b);
	v_eyeVec.z = dot(tmpVec, n);
}
