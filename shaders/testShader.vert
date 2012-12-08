varying vec3 lightVec; 
varying vec3 eyeVec;
varying vec2 texCoord;
//attribute vec3 vTangent; 
uniform float time;
uniform float speed;
//contains ideas from http://www.ozone3d.net/tutorials/bump_mapping_p3.php
void main(void)
{
  	vec4 position = vec4(gl_Vertex);
  	float radius;
   // change to if then..
  	radius = (position.z < 1.0) ? (position.z / 1.0): ((10.0 - position.z) / 1.0);
  	position.xy *= (position.z < 1.0 || position.z > 9.0) ? radius : 1.0;
  	position.xy = position.xy * 0.5;
  	
    float angle = position.z * 0.5 + time * 1.0 * speed;
  	
    position.y += abs(sin(angle));
    
    gl_Position = gl_ModelViewProjectionMatrix * position;
//	gl_Position = ftransform();
	texCoord = gl_MultiTexCoord0.xy;
    // hack to get approx tangents.. taken from http://www.ozone3d.net/tutorials/mesh_deformer_p2.php#tangent_space
    vec3 c1 = cross(gl_Normal, vec3(0.0, 0.0, 1.0)); 
    vec3 c2 = cross(gl_Normal, vec3(0.0, 1.0, 0.0)); 
    vec3 tangent;   
    if(length(c1)>length(c2))
    {
    	tangent = c1;	
    }
    else
    {
    	tangent = c2;	
    }
	
	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * tangent);
	vec3 b = cross(n, t);
	
	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 tmpVec = gl_LightSource[0].position.xyz - vVertex;
    
	lightVec.x = dot(tmpVec, t);
	lightVec.y = dot(tmpVec, b);
	lightVec.z = dot(tmpVec, n);
    
	tmpVec = -vVertex;
	eyeVec.x = dot(tmpVec, t);
	eyeVec.y = dot(tmpVec, b);
	eyeVec.z = dot(tmpVec, n);
}

