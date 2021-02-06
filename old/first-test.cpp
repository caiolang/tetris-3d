// #define _USE_MATH_DEFINES
// #include <math.h>
// #include <iostream>
// #include <ctime>

// #ifdef __APPLE__
// #include <OpenGL/gl.h>
// #else
// #include <GL/gl.h>
// #endif

// #ifdef __APPLE__
// #include <GLUT/glut.h>
// #else
// #include <GL/glut.h>
// #endif

// #include <OpenGL/glu.h>

// struct float2
// {
//     float2( float _x = 0.0f, float _y = 0.0f ) : x(_x), y(_y) {}
 
//     float x;
//     float y;
// };
 
// struct float3
// {
//     float3( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f ) : x(_x), y(_y), z(_z) {}
 
//     float x;
//     float y;
//     float z;
// };

// /* Global variables that will be used by GLUT to initialize the render window: */
// int g_iWindowWidth = 512;
// int g_iWindowHeight = 512;
// int g_iGLUTWindowHandle = 0;
// /* If an error occurs, we will use a global error code to report the error when the application exists. */
// int g_iErrorCode = 0;

// /* OpenGL Callback functions prototypes */
// void InitGL( int argc, char* argv[] );
// void DisplayGL();
// void IdleGL();
// void KeyboardGL( unsigned char c, int x, int y );
// void MouseGL( int button, int state, int x, int y );
// void MotionGL( int x, int y );
// void ReshapeGL( int w, int h );

// /* Prototypes of functions used to declare primitives */
// void DrawRectangle( float width, float height );
// void DrawCircle( float radius, int numSides = 8 );
// void DrawTriangle( float2 p1, float2 p2, float2 p3 );
// /* 3D */
// void DrawCube( float width, float height, float depth );
// void DrawSphere( float radius );
// void DrawPyramid( float scale = 1.0f );

// /* Enumeration to store the different scene types and a variable to store the current value. */
// enum ESceneType
// {
//     ST_Scene1 = 0,
//     ST_Scene2,
//     ST_Scene3,
//     ST_Scene4,
//     ST_NumScenes
// };
// ESceneType g_eCurrentScene = ST_Scene1;

// /* Variables to store the rotatation of each primitive */
// float g_fRotate1 = 0.0f;
// float g_fRotate2 = 0.0f;
// float g_fRotate3 = 0.0f;

// /* Number of ticks between frames */
// std::clock_t g_PreviousTicks;
// std::clock_t g_CurrentTicks;

// // Render a simple scene with 2D primitives
// void RenderScene1();
// // Render a slightly more complex scene using different colors
// void RenderScene2();
// // Render a scene with animated transformations
// void RenderScene3();
// // Render a scene with 3D objects that perform rotations on all 3 axis.
// void RenderScene4();

// /* Cleans up all resources */
// void Cleanup( int exitCode, bool bExit = true );

// // ----------------------------------

// int main( int argc, char* argv[] )
// {
//     // Capture the previous time to calculate the delta time on the next frame
//     g_PreviousTicks = std::clock();
 
//     InitGL( argc, argv );
//     glutMainLoop();
// }

// void Cleanup( int errorCode, bool bExit )
// {
//     if ( g_iGLUTWindowHandle != 0 )
//     {
//         glutDestroyWindow( g_iGLUTWindowHandle );
//         g_iGLUTWindowHandle = 0;
//     }
 
//     if ( bExit )
//     {
//         exit( errorCode );
//     }
// }

// ----------------------------------

//thanks to http://stackoverflow.com/questions/7879843/opengl-hello-world-on-mac-without-xcode

//build with:

//c++ /System/Library/Frameworks/GLUT.framework/GLUT /System/Library/Frameworks/OpenGL.framework/OpenGL main.cpp -o demo-osx-glut.app

//to be tested:
//CUDA:   nvcc -o demo-osx-glut.app demo-osx-glut.cxx -Xlinker -framework,OpenGL,-framework,GLUT
//http://stackoverflow.com/questions/2498749/how-can-i-use-glut-with-cuda-on-macosx

// The OpenGL libraries, make sure to include the GLUT and OpenGL frameworks
// #include <GLUT/glut.h>
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif


#include <iostream>
// This is just an example using basic glut functionality.
// If you want specific Apple functionality, look up AGL

void init() // Called before main loop to set up the program
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

// Called at the start of the program, after a glutPostRedisplay() and during idle
// to display a frame
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.0, 0.0, -10.0);
        glVertex3f(1.0, 0.0, -10.0);
        glVertex3f(0.0, 1.0, -10.0);
    glEnd();

    glutSwapBuffers();
}

// Called every time a window is resized to resize the projection matrix
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.2, 9999999.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initializes glut

    // Sets up a double buffer with RGBA components and a depth component
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    // Sets the window size to 512*512 square pixels
    glutInitWindowSize(512, 512);

    // Sets the window position to the upper left
    glutInitWindowPosition(0, 0);

    // Creates a window using internal glut functionality
    glutCreateWindow("Hello!");

    // passes reshape and display functions to the OpenGL machine for callback
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);

    init();

    // Starts the program.
    glutMainLoop();
    return 0;
}