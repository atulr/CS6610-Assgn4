#include "utilities.h"


const GLcharARB* loadSource(const char* filename) 
{
	std::string buf;
	std::string line;
	
	std::ifstream in(filename);
	
	if (!in) {
		fprintf(stderr, "Could not find file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	
	while (std::getline(in,line)) {
		buf += line; buf += '\n';
	}
	
	GLcharARB* ret = (GLcharARB*)malloc(buf.size()+1);
	strncpy(ret, buf.c_str(), buf.size());
	ret[buf.size()] = '\0';
	
	return ret;
}


void cleanupShader(GLhandleARB & glsl_program, GLhandleARB & vertexShader, GLhandleARB & fragmentShader){
    // Clean up
	glDeleteObjectARB(vertexShader);
	glDeleteObjectARB(fragmentShader);
    glDeleteObjectARB(glsl_program);
}

void createShader(GLhandleARB & glsl_program, GLhandleARB & vertexShader, GLhandleARB & fragmentShader, std::string vertexShader_filename, std::string fragmentShader_filename)
{
	const GLcharARB* vertex_shader_source;
	const GLcharARB* fragment_shader_source;
	GLint status;
	
	// Create the OpenGL shader objects
	glsl_program    = glCreateProgramObjectARB();
	vertexShader   = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
	// Load the source code
	vertex_shader_source = loadSource(vertexShader_filename.c_str());
	fragment_shader_source = loadSource(fragmentShader_filename.c_str());
	
	glShaderSourceARB(vertexShader, 1, &vertex_shader_source, NULL);
	glShaderSourceARB(fragmentShader, 1, &fragment_shader_source, NULL);
	
	delete vertex_shader_source;
	delete fragment_shader_source;
	
	
	// Compile the shaders
	glCompileShaderARB(vertexShader);
	glGetObjectParameterivARB(vertexShader, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	if( GL_FALSE == status ) {
		// Get the InfoLog and print the compilation error
		GLint msglen;
		glGetObjectParameterivARB(vertexShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &msglen);
		GLcharARB* msg = (GLcharARB*)malloc(msglen);
		glGetInfoLogARB(vertexShader, msglen, NULL, msg);
        std::cout << "Error compiling vertex shader : " << msg << std::endl;
		free(msg);
		exit(EXIT_FAILURE);
	}
	
	glCompileShaderARB(fragmentShader);
	glGetObjectParameterivARB(fragmentShader, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	if( GL_FALSE == status ) {
		// Get the InfoLog and print the compilation error
		GLint msglen;
		glGetObjectParameterivARB(fragmentShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &msglen);
		GLcharARB* msg = (GLcharARB*)malloc(msglen);
		glGetInfoLogARB(fragmentShader, msglen, NULL, msg);
        std::cout << "Error compiling fragment shader : " << msg << std::endl;
		free(msg);
		exit(EXIT_FAILURE);
	}
	
	// Attach the compiled shader to the program object
	glAttachObjectARB(glsl_program, vertexShader);
	glAttachObjectARB(glsl_program, fragmentShader);
	
	// Link the program
	glLinkProgramARB(glsl_program);
	glGetObjectParameterivARB(glsl_program, GL_OBJECT_LINK_STATUS_ARB, &status);
	if( GL_FALSE == status ) {
		// Get the InfoLog and print the linking error
		GLint msglen;
		glGetObjectParameterivARB(glsl_program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &msglen);
		GLcharARB* msg = (GLcharARB*)malloc(msglen);
		glGetInfoLogARB(glsl_program, 1024, NULL, msg);
        std::cout << "Error linking GLSL program : " << msg << std::endl;
		free(msg);
		exit(EXIT_FAILURE);
	}
}

