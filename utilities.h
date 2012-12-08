#ifndef UTILITIES
#define UTILITIES

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include "GL/glut.h"
#endif

#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////
// Shader functions

const GLcharARB* loadSource(const char* filename);
void cleanupShader(GLhandleARB & glsl_program, GLhandleARB & vertexShader, GLhandleARB & fragmentShader);
void createShader(GLhandleARB & glsl_program, GLhandleARB & vertexShader, GLhandleARB & fragmentShader, std::string vertexShader_filename, std::string fragmentShader_filename);


//////////////////////////////////////////////////////////////////////////
// Inline defined functions

// Some maths stuff
inline void normalize(float v[3]){
	float l = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	l = 1 / (float)sqrt(l);
    
	v[0] *= l;  v[1] *= l;  v[2] *= l;
}

inline void crossproduct(float a[3], float b[3], float res[3]){
	res[0] = (a[1] * b[2] - a[2] * b[1]);
	res[1] = (a[2] * b[0] - a[0] * b[2]);
	res[2] = (a[0] * b[1] - a[1] * b[0]);
}

inline float length(float v[3]){
	return (float)sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}



// useful opengl debug
inline GLenum checkGLFrameBufferError(GLenum target, std::string message ="", bool warmNoError = false){
    GLenum err = glCheckFramebufferStatus(target);
    
    switch (err){
        case GL_FRAMEBUFFER_UNDEFINED: std::cout << "At " << message  << ":  " << "GL_FRAMEBUFFER_UNDEFINED: The target is the default framebuffer, but the default framebuffer does not exist" << std::endl;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: std::cout << "At " << message  << ":  " <<  "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: Some/All of the framebuffer attachment points are framebuffer incomplete" << std::endl; break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: std::cout << "At " << message  << ":  " << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: The framebuffer does not have at least one image attached to it" << std::endl;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: std::cout << "At " << message  << ":  " << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAWBUFFERi." << std::endl;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: std::cout << "At " << message  << ":  " << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: The GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER" << std::endl;
            break;
            
        case GL_FRAMEBUFFER_UNSUPPORTED: std::cout << "At " << message  << ":  " <<"GL_FRAMEBUFFER_UNSUPPORTED: The combination of internal formats of the attached images violates an implementation-dependent set of restrictions" << std::endl;
            break;
            
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            std::cout << "At " << message  << ":  " << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES" << std::endl;
            std::cout << "At " << message  << ":  " << "or the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures" << std::endl;
            break;
            
            // case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: 	std::cout << "The framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target" << std::endl; break;
            
        case GL_INVALID_ENUM:
            std::cout << "At " << message  << ":  " << "generated if target is not GL_DRAW_FRAMEBUFFER, GL_READ_FRAMEBUFFER or GL_FRAMEBUFFER." << std::endl;
            break;
            
        default:
            if (warmNoError == true)
                std::cout << "No error - you are all good!" << std::endl;
    }
    
    return err;
}

inline GLenum checkGLError(std::string message ="", bool warmNoError = false){
    GLenum err = glGetError();
    
    switch (err){
        case GL_INVALID_ENUM: std::cout << "At " << message  << ":  "<< "GL_INVALID_ENUM: Given when an enumeration parameter contains an enum that is not allowed for that function" << std::endl; break;
            
        case GL_INVALID_VALUE: std::cout << "At " << message  << ":  "<< "GL_INVALID_VALUE: Given when a numerical parameter does not conform to the range requirements that the function places upon it" << std::endl; break;
            
        case GL_INVALID_OPERATION: std::cout << "At " << message  << ":  "<< "GL_INVALID_OPERATION: Given when the function in question cannot be executed because of state that has been set in the context" << std::endl; break;
            
        case GL_OUT_OF_MEMORY: std::cout << "At " << message  << ":  "<< "GL_OUT_OF_MEMORY: Given when performing an operation that can allocate memory, when the memory in question cannot be allocated" << std::endl; break;
            
        case GL_STACK_OVERFLOW: std::cout << "At " << message  << ":  "<< " GL_STACK_OVERFLOW: Deprecated - Given when a stack pushing operation causes a stack to overflow the limit of that stack's size." << std::endl; break;
            
        case GL_STACK_UNDERFLOW: std::cout << "At " << message  << ":  "<< "GL_STACK_UNDERFLOW: Deprecated - Given when a stack popping operation is given when the stack is already at its lowest point." << std::endl; break;
            
        case GL_TABLE_TOO_LARGE: std::cout << "At " << message  << ":  "<< "GL_TABLE_TOO_LARGE: This error code is a part of the GL_ARB_imaging extention " << std::endl; break;
            
        case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "At " << message  << ":  "<< "GL_INVALID_FRAMEBUFFER_OPERATION: Check for framebuffer errors instead; these things have their own code!!!" << std::endl;
            break;
            
        case GL_NO_ERROR:
            if (warmNoError == true)
                std::cout << "At " << message << "  No error - you are all good!" << std::endl;
            break;
            
        default:
            std::cout << "At " << message << "  Something else which is not getting caught with code: " << err << std::endl;
            
    }
    
    return err;
}

#endif
