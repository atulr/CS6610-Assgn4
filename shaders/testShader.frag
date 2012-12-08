uniform int option;
uniform sampler2D sampler0;
void main(){
    
    vec4 sceneColor = texture2D(sampler0, gl_TexCoord[0].st);    
    // set the color based on uniform passed
    gl_FragColor = sceneColor;
}
