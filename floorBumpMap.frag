varying vec4 position;			

uniform sampler2D sampler0;

void main( void ) 
{ 
	vec3 normalTex = texture2D(sampler0, gl_TexCoord[0].st).xyz; 
    normalTex = (normalTex - 0.5) * 2.0;
	vec3 normal = normalize(normalTex);
	
	vec3 lightDir = normalize(vec3(gl_LightSource[0].position - position)); 
	float nDotL = max(dot(normal, lightDir), 0.0); 
    
	vec4 finalcolor = texture2D(sampler0, gl_TexCoord[0].st); 
    finalcolor *= gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * nDotL;
	
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	vec4 globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
    
	gl_FragColor = min(finalcolor + ambient + globalAmbient, vec4(1.0)); 
} 