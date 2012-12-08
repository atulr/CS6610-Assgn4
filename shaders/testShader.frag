//uniform int option;
//uniform sampler2D sampler0;
//uniform sampler2D sampler1;
//varying vec3 eyeVector; 
//varying vec3 lightVec;
//varying vec2 texCoord;
//varying vec3 normal;
//void main(){
//  
//    vec4 color;
//	vec4 specular;
//	
//	vec3 normalTex = texture2D(sampler1, texCoord).xyz;
//	normalTex = (normalTex * 2.0) - 1.0;
//	vec3 newNormal = normalize(normalTex);
//	
//	float NdotL = max(dot(newNormal, lightVec), 0.0);
//	
//	vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
//	
//	vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
//	vec4 globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
//	
//    vec4 textureColor = texture2D(sampler0, texCoord);
//	
//	vec3 halfVec = normalize(lightVec + eyeVector);
//	
//	if (NdotL > 0.0)
//	{
//		float NdotHV = max(dot(newNormal, halfVec), 0.0);
//		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV, gl_FrontMaterial.shininess);
//	}
//	
//	gl_FragColor = min(textureColor * NdotL * diffuse + ambient + globalAmbient + specular, vec4(1.0));	
//
//}

varying vec3 lightVec;
varying vec3 eyeVec;
varying vec2 texCoord;
uniform sampler2D sampler0;
uniform sampler2D sampler1;


void main (void)
{
	float distSqr = dot(lightVec, lightVec);
    float att = 1.0;
	vec3 lVec = lightVec * inversesqrt(distSqr);
    
	vec3 vVec = normalize(eyeVec);
	
	vec4 base = texture2D(sampler0, texCoord);
	
	vec3 bump = normalize( texture2D(sampler1, texCoord).xyz * 2.0 - 1.0);
    float NdotL = max(dot(bump, lightVec), 0.0);
	vec4 vAmbient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;
    
	float diffuse = max( dot(lVec, bump), 0.0 );
	
	vec4 vDiffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * 
    diffuse;	
    vec4 specular;
    	vec3 halfVec = normalize(lightVec + eyeVec);
    	
    //	if (NdotL > 0.0)
    //	{
    		float NdotHV = max(dot(bump, halfVec), 0.0);
    		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV, gl_FrontMaterial.shininess);
    //	}
    
//	float specular = pow(clamp(dot(reflect(-lVec, bump), vVec), 0.0, 1.0), 
//                         gl_FrontMaterial.shininess );
	
	vec4 vSpecular = gl_LightSource[0].specular * gl_FrontMaterial.specular * 
    specular;	
	
	gl_FragColor = ( vAmbient*base + 
                    vDiffuse*base + 
                    vSpecular) * att;
    
}
