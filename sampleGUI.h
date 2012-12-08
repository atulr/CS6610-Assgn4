#ifndef getting_started_sampleGUI
#define getting_started_sampleGUI

#include "texture.h"
#include "Color.h"
#include "utilities.h"

#include "GL/glui.h"



//////////////////////////////////////////////////////////////////////////
// Some constants
// the user id's that we can use to identify which control
// caused the callback to be called
#define CB_DEPTH_BUFFER 0
#define CB_ACTION_BUTTON 1
#define CB_RESET 2
#define TEX_CAPTURE 3
#define RELOAD_SHADER 4
#define CB_EXIT 10



//////////////////////////////////////////////////////////////////////////
// Global variables


// shader variables
GLhandleARB  glsl_program_test;
GLhandleARB  vertexShader_test;
GLhandleARB  fragmentShader_test;

GLhandleARB  glslBumpMap;
GLhandleARB  bumpMapVertexShader;
GLhandleARB  bumpMapFragmentShader;

GLint option_handle;

int live_optionValue;


// main window
int	main_window;

// the camera info
float eye[3];
float lookat[3];

// more textures
GLuint fboId;
GLuint textureCapture;
int texSizeX = 512;
int texSizeY = 512;
int texCapture = 0;


// mouse handling functions for the main window
// left mouse translates, middle zooms, right rotates
// keep track of which button is down and where the last position was
int cur_button = -1;
int last_x;
int last_y;


// pointers for all of the glui controls
GLUI *glui;
GLUI_Rollout		*object_rollout;
GLUI_RadioGroup		*object_type_radio;
GLUI_Rotation		*object_rotation;
GLUI_Translation	*object_xz_trans;
GLUI_Translation	*object_y_trans;

GLUI_Rollout		*anim_rollout;
GLUI_Button			*action_button;

GLUI_Checkbox *draw_floor_check;
GLUI_Checkbox *draw_object_check;

// This  checkbox utilizes the callback
GLUI_Checkbox *use_depth_buffer;


// walking action variables
//
GLfloat step = 0;
GLfloat live_anim_speed = 3;


// live variables
// each of these are associated with a control in the interface.
// when the control is modified, these variables are automatically updated
int live_object_type;	// 0=cube, 1=sphere, 2=torus
float live_object_rotation[16];
float live_object_xz_trans[2];
float live_object_y_trans;
int live_draw_floor;
int live_draw_object;
int live_use_depth_buffer;
int live_texture_capture;


//////////////////////////////////////////////////////////////////////////
// Functions

// OpenGL stuff
void initGL();              // initialize some states
void drawScene();           // draws the scene
void drawSolidCylinder();          // draws an object in the scene
void drawWireFrameCylinder();
int setUpFrameBufferObj();  // sets up a FBO
void captureSceneToTexture();


// opengl callbacks that need to the registered
void myGlutDisplay(	void );                 // drawing the scene goes here
void myGlutIdle(void);                      // reswitching focus

void myGlutMouse(int button, int state, int x, int y);  // catch mouse up/down events
void myGlutKeyboard(unsigned char key, int x, int y);   // you can put keyboard shortcuts in here

void myGlutReshape(int	x, int y);                      // the window has changed shapes, fix ourselves up


// UI
void initGLUI();                // init the UI code
void glui_cb(int control);      // some controls generate a callback when they are changed


// Shaders
void initUniformVars();

//-----------------------------------------------------------------------------
// Name: writeTextureToPPM
// Desc: writes a ppm image
// Source: from Liang
// Example use: writeTextureToPPM("output/final", textureBuffer[readTex], textureDim,textureDim, GL_RGBA, GL_UNSIGNED_BYTE);
//-----------------------------------------------------------------------------
inline void writeTextureToPPM( const char* fileName , GLuint tex, GLuint m_iSizeX, GLuint m_iSizeY, GLenum m_format, GLenum m_type)
{
    //cout << "m_iSizeX: " <<m_iSizeX << "  m_iSizeY: " << m_iSizeY << endl;
    GLuint m_iSizePerElement = sizeof(GL_UNSIGNED_BYTE);
    
    unsigned char*content = new unsigned char[m_iSizeX * m_iSizeY * m_iSizePerElement];
    glBindTexture(GL_TEXTURE_2D, tex);
    glGetTexImage(GL_TEXTURE_2D, 0, m_format, m_type, content);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    Image img(m_iSizeX, m_iSizeY);
    // Image img(m_iSizeXX, m_iSizeYY);
    
    
    for(GLuint y = 0; y < m_iSizeY; y++){
        for(GLuint x = 0; x < m_iSizeX; x++){
            Color C;
            size_t index = y * m_iSizeX + x;
            double alpha = double(content[4 * index + 3]) / 255.0;
            //alpha = 1.0;
            C.set_r(double(content[4 * index + 0]) / 255.0 * alpha);
            C.set_g(double(content[4 * index + 1]) / 255.0 * alpha);
            C.set_b(double(content[4 * index + 2]) / 255.0 * alpha);
            img.set(x, y, C);
        }
    }
    img.write(std::string(fileName) + ".ppm");
    
    delete [] content;
	content = NULL;
}

#endif
