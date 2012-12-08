uniform vec4 endPositions;
uniform float numberWiggles;
uniform float time;
uniform float speed;


void main(){
    
	vec4 position = vec4(gl_Vertex);
	float radius;
    
	radius = (position.z < 1.0) ? (position.z / 1.0): ((10.0 - position.z) / 1.0);
	position.xy *= (position.z < 1.0 || position.z > 9.0) ? radius : 1.0;
	position.xy = position.xy * 0.33;
	
    float angle = position.z * (3.0 / 2.0) + 2.0 * 0.1 * 2.0;
	
    position.y += abs(sin(angle));
    
	gl_Position = gl_ModelViewProjectionMatrix * position;
    gl_TexCoord[0] = gl_MultiTexCoord0;   
}