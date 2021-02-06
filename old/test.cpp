#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif


struct float2
{
    float2( float _x = 0.0f, float _y = 0.0f ) : x(_x), y(_y) {}
 
    float x;
    float y;
};
 
struct float3
{
    float3( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f ) : x(_x), y(_y), z(_z) {}
 
    float x;
    float y;
    float z;
};

/* Global variables that will be used by GLUT to initialize the render window: */
int g_iWindowWidth = 512;
int g_iWindowHeight = 512;
int g_iGLUTWindowHandle = 0;
/* If an error occurs, we will use a global error code to report the error when the application exists. */
int g_iErrorCode = 0;

/* OpenGL Callback functions prototypes */
void InitGL( int argc, char* argv[] );
void DisplayGL();
void IdleGL();
void KeyboardGL( unsigned char c, int x, int y );
void MouseGL( int button, int state, int x, int y );
void MotionGL( int x, int y );
void ReshapeGL( int w, int h );

/* Prototypes of functions used to declare primitives */
void DrawRectangle( float width, float height );
void DrawCircle( float radius, int numSides = 8 );
void DrawTriangle( float2 p1, float2 p2, float2 p3 );
/* 3D */
void DrawCube( float width, float height, float depth );
void DrawSphere( float radius );
void DrawPyramid( float scale = 1.0f );

/* Enumeration to store the different scene types and a variable to store the current value. */
enum ESceneType
{
    ST_Scene1 = 0,
    ST_Scene2,
    ST_Scene3,
    ST_Scene4,
    ST_NumScenes
};
ESceneType g_eCurrentScene = ST_Scene1;

/* Variables to store the rotatation of each primitive */
float g_fRotate1 = 0.0f;
float g_fRotate2 = 0.0f;
float g_fRotate3 = 0.0f;

/* Number of ticks between frames */
std::clock_t g_PreviousTicks;
std::clock_t g_CurrentTicks;

// Render a simple scene with 2D primitives
void RenderScene1();
// // Render a slightly more complex scene using different colors
// void RenderScene2();
// // Render a scene with animated transformations
// void RenderScene3();
// // Render a scene with 3D objects that perform rotations on all 3 axis.
// void RenderScene4();

/* Cleans up all resources */
void Cleanup( int exitCode, bool bExit = true );

// ----------------------------------

int main( int argc, char* argv[] )
{
    // Capture the previous time to calculate the delta time on the next frame
    g_PreviousTicks = std::clock();
 
    InitGL( argc, argv );
    glutMainLoop();
}

void Cleanup( int errorCode, bool bExit )
{
    if ( g_iGLUTWindowHandle != 0 )
    {
        glutDestroyWindow( g_iGLUTWindowHandle );
        g_iGLUTWindowHandle = 0;
    }
 
    if ( bExit )
    {
        exit( errorCode );
    }
}

void InitGL( int argc, char* argv[] )
{
    std::cout << "Initialise OpenGL..." << std::endl;
 
    glutInit(&argc, argv);
    int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);
 
    glutInitDisplayMode( GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH );
 
    glutInitWindowPosition( ( iScreenWidth - g_iWindowWidth ) / 2,
                            ( iScreenHeight - g_iWindowHeight ) / 2 );
    glutInitWindowSize( g_iWindowWidth, g_iWindowHeight );
 
    g_iGLUTWindowHandle = glutCreateWindow( "OpenGL" );
 
    // Register GLUT callbacks
    glutDisplayFunc(DisplayGL);
    glutIdleFunc(IdleGL);
    glutMouseFunc(MouseGL);
    glutMotionFunc(MotionGL);
    glutKeyboardFunc(KeyboardGL);
    glutReshapeFunc(ReshapeGL);
 
    // Setup initial GL State
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f ); // Color used to clear the color buffer
    glClearDepth( 1.0f );
 
    glShadeModel( GL_SMOOTH ); // Specifiec the shading model
    std::cout << "Initialise OpenGL: Success!" << std::endl;
}

void DisplayGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    switch ( g_eCurrentScene )
    {
    case ST_Scene1:
        {RenderScene1();}
        break;
    case ST_Scene2:
        {RenderScene2();}
        break;
    case ST_Scene3:
        {RenderScene3();}
        break;
    case ST_Scene4:
        {RenderScene4();}
        break;
    }
 
    glutSwapBuffers();
    glutPostRedisplay();
}

/*
* Will be invoked whenever there are no events to be processed in the GLUT even loop.
* We will use this method to update the logic of our demo.
*/
void IdleGL()
{
    // Update our simulation
    g_CurrentTicks = std::clock();
    float deltaTicks = ( g_CurrentTicks - g_PreviousTicks );
    g_PreviousTicks = g_CurrentTicks;
 
    float fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;
 
    // Rate of rotation in (degrees) per second
    const float fRotationRate = 50.0f;
 
    // Update our rotation parameters
    g_fRotate1 += ( fRotationRate * fDeltaTime );
    g_fRotate1 = fmodf( g_fRotate1, 360.0f );
 
    g_fRotate2 += ( fRotationRate * fDeltaTime );
    g_fRotate2 = fmodf( g_fRotate2, 360.0f );
 
    g_fRotate3 += ( fRotationRate * fDeltaTime );
    g_fRotate3 = fmodf( g_fRotate3, 360.0f );
 
    glutPostRedisplay();
}


/*
* Defines what each key does , when pressed
*/
void KeyboardGL( unsigned char c, int x, int y )
{
    // Store the current scene so we can test if it has changed later.
    ESceneType currentScene = g_eCurrentScene;
 
    switch ( c )
    {
    case '1':
        {
            glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );                         // White background
            g_eCurrentScene = ST_Scene1;
        }
        break;
    case '2':
        {
            glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );                         // Black background
            g_eCurrentScene = ST_Scene2;
        }
        break;
    case '3':
        {
            glClearColor( 0.27f, 0.27f, 0.27f, 1.0f );                      // Dark-Gray background
            g_eCurrentScene = ST_Scene3;
        }
        break;
    case '4':
        {
            glClearColor( 0.73f, 0.73f, 0.73f, 1.0f );                      // Light-Gray background
            g_eCurrentScene = ST_Scene4;
        }
        break;
    case 's':
    case 'S':
        {
            std::cout << "Shade Model: GL_SMOOTH" << std::endl;
            // Switch to smooth shading model
            glShadeModel( GL_SMOOTH );
        }
        break;
    case 'f':
    case 'F':
        {
            std::cout << "Shade Model: GL_FLAT" << std::endl;
            // Switch to flat shading model
            glShadeModel( GL_FLAT );
        }
        break;
    case 'r':
    case 'R':
        {
            std::cout << "Reset Parameters..." << std::endl;
            g_fRotate1 = g_fRotate2 = g_fRotate3 = 0.0f;
        }
        break;
    case '\033': // escape quits
    case '\015': // Enter quits
    case 'Q':    // Q quits
    case 'q':    // q (or escape) quits
        {
            // Cleanup up and quit
            Cleanup(0);
        }
        break;
    }
 
    if ( currentScene != g_eCurrentScene )
    {
        std::cout << "Changed Render Scene: " << ( g_eCurrentScene + 1 ) << std::endl;
    }
 
    glutPostRedisplay();
}

// Not used for the moment
void MouseGL( int button, int state, int x, int y )
{
 
}
 
// Not used for the moment
void MotionGL( int x, int y )
{
 
}

void ReshapeGL( int w, int h )
{
    std::cout << "ReshapGL( " << w << ", " << h << " );" << std::endl;
 
    if ( h == 0)                                        // Prevent a divide-by-zero error
    {
        h = 1;                                      // Making Height Equal One
    }
 
    g_iWindowWidth = w;
    g_iWindowHeight = h;
 
    glViewport( 0, 0, g_iWindowWidth, g_iWindowHeight );
 
    // Setup the projection matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, (GLdouble)g_iWindowWidth/(GLdouble)g_iWindowHeight, 0.1, 100.0 );
 
    glutPostRedisplay();
}

/* Primitive-drawing functions, using OpenGL immediate mode */
void DrawTriangle( float2 p1, float2 p2, float2 p3 )
{
    glBegin( GL_TRIANGLES );
        glVertex2f( p1.x, p1.y );
        glVertex2f( p2.x, p2.y );
        glVertex2f( p3.x, p3.y );
    glEnd();
}
 
void DrawRectangle( float width, float height )
{
    const float w = width / 2.0f;
    const float h = height / 2.0f;
 
    glBegin( GL_QUADS );
        glVertex2f( -w,  h );   // Top-Left
        glVertex2f(  w,  h );   // Top-Right
        glVertex2f(  w, -h );   // Bottom-Right
        glVertex2f( -w, -h );   // Bottom-Left
    glEnd();
 
}
 
void DrawCircle(  float radius, int numSides /* = 8 */ )
{
    const float step = M_PI / numSides;
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f(0.0f, 0.0f);
        for ( float angle = 0.0f; angle < ( 2.0f * M_PI ); angle += step )
        {
            glVertex2f( radius * sinf(angle), radius * cosf(angle) );
        }
        glVertex2f( 0.0f, radius ); // One more vertex to close the circle
    glEnd();
}

void RenderScene1()
{
    glMatrixMode( GL_MODELVIEW );                                           // Switch to modelview matrix mode
    glLoadIdentity();                                                       // Load the identity matrix
 
    glTranslatef( -1.5f, 1.0f, -6.0f );                                     // Translate our view matrix back and a bit to the left.
    glColor3f( 1.0f, 0.0f, 0.0f );                                          // Set Color to red
    DrawTriangle( float2(0.0f, 1.0f), float2(-1.0f, -1.0f), float2(1.0f, -1.0f ) );
 
    glTranslatef( 3.0f, 0.0f, 0.0f );                                       // Shift view 3 units to the right
    glColor3f( 0.0f, 0.0f, 1.0f );                                          // Set Color to blue
    DrawRectangle( 2.0f, 2.0f );
 
    glTranslatef( -1.5f, -3.0f, 0.0f );                                     // Back to center and lower screen
    glColor3f( 1.0f, 1.0f, 0.0f );                                          // Set color to yellow
    DrawCircle( 1.0f, 16 );
}

// ----------------------------------
// template from : https://gist.github.com/petrifast/4403998

//build with:
//c++ /System/Library/Frameworks/GLUT.framework/GLUT /System/Library/Frameworks/OpenGL.framework/OpenGL main.cpp -o demo-osx-glut.app

// The OpenGL libraries, make sure to include the GLUT and OpenGL frameworks
// #include <GLUT/glut.h>
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>

// #ifdef __APPLE__
// #include <GLUT/glut.h>
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
// #else
// #include <GL/glut.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
// #endif


// #include <iostream>
// // This is just an example using basic glut functionality.
// // If you want specific Apple functionality, look up AGL

// void init() // Called before main loop to set up the program
// {
//     glClearColor(0.0, 0.0, 0.0, 0.0);
//     glEnable(GL_DEPTH_TEST);
//     glShadeModel(GL_SMOOTH);
// }

// // Called at the start of the program, after a glutPostRedisplay() and during idle
// // to display a frame
// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();

//     glBegin(GL_TRIANGLES);
//         glVertex3f(0.0, 0.0, -10.0);
//         glVertex3f(1.0, 0.0, -10.0);
//         glVertex3f(0.0, 1.0, -10.0);
//     glEnd();

//     glutSwapBuffers();
// }

// // Called every time a window is resized to resize the projection matrix
// void reshape(int w, int h)
// {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.2, 9999999.0);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
// }


// int main(int argc, char **argv)
// {
//     glutInit(&argc, argv); // Initializes glut

//     // Sets up a double buffer with RGBA components and a depth component
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

//     // Sets the window size to 512*512 square pixels
//     glutInitWindowSize(512, 512);

//     // Sets the window position to the upper left
//     glutInitWindowPosition(0, 0);

//     // Creates a window using internal glut functionality
//     glutCreateWindow("Hello!");

//     // passes reshape and display functions to the OpenGL machine for callback
//     glutReshapeFunc(reshape);
//     glutDisplayFunc(display);
//     glutIdleFunc(display);

//     init();

//     // Starts the program.
//     glutMainLoop();
//     return 0;
// }