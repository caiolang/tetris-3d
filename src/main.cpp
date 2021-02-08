#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>
// #include <string.h>
#include "Cube.h"
#include "Matrix.h"
#include "Piece.h"
#include "O_piece.h"

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

int g_iWindowWidth = 512;
int g_iWindowHeight = 512;
int g_iGLUTWindowHandle = 0;
int g_iErrorCode = 0;

Matrix *matrix = new Matrix();
const int MATRIX_SIZE = 2200;
const int X_DIM = 10;
const int Y_DIM = 22;
const int Z_DIM = 10;
// unsigned char hello_string[] = "The quick god jumps over the lazy brown fox.";
// int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, hello_string);


void InitGL( int argc, char* argv[] );
void DisplayGL();
void IdleGL();
void KeyboardGL( unsigned char c, int x, int y );
void MouseGL( int button, int state, int x, int y );
void MotionGL( int x, int y );
void ReshapeGL( int w, int h );

// 2D Primitives
void DrawRectangle( float width, float height );
void DrawCircle( float radius, int numSides = 8 );
void DrawTriangle( float2 p1, float2 p2, float2 p3 );

// 3D Primitives
void DrawCube( float width, float height, float depth );
void DrawSphere( float radius );
void DrawPyramid( float scale = 1.0f );

int id_to_x(int id);
int id_to_y(int id);
int id_to_z(int id);

enum ESceneType
{
    ST_Scene1 = 0,
    ST_Scene2,
    ST_Scene3,
    ST_Scene4,
    ST_NumScenes
};
ESceneType g_eCurrentScene = ST_Scene1;

// Rotation parameters
float g_fRotate1 = 0.0f;
float g_fRotate2 = 0.0f;
float g_fRotate3 = 0.0f;

std::clock_t g_PreviousTicks;
std::clock_t g_CurrentTicks;

// Render a test scene
void RenderScene1();
// Render the matrix 
void RenderScene2(); 
// Render a scene with animated transformations
void RenderScene3();
// Render a scene with 3D objects that perform rotations on all 3 axis.
void RenderScene4();

// We're exiting, cleanup the allocated resources.
void Cleanup( int exitCode, bool bExit = true );

int main( int argc, char* argv[] )
{
    // Capture the previous time to calculate the delta time on the next frame
    g_PreviousTicks = std::clock();

    // Matrix *matrix = new Matrix();
 

    // for (size_t i = 0; i < MATRIX_SIZE; i++)
    // {
    //     std::cout << matrix->get_cubes()[i]; // << "\n";
    // }
    
    O_piece *test_piece = new O_piece();

      for (size_t i = 0; i < 4; i++)
    {
        std::cout << test_piece->get_cubes()[i] << ",";
        
    }

    int new_pos[4];
    test_piece->rotate_x(new_pos);
    std::cout << std::endl <<"New Position:"<< std::endl;
    for (size_t i = 0; i < 4; i++)
    {
        std::cout << new_pos[i] << ",";
    }

    InitGL( argc, argv );
    glutMainLoop();
    Cleanup(g_iErrorCode);
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

    g_iGLUTWindowHandle = glutCreateWindow( "Tetris 3D" );

    // Register GLUT callbacks
    glutDisplayFunc(DisplayGL);
    glutIdleFunc(IdleGL);
    glutMouseFunc(MouseGL);
    glutMotionFunc(MotionGL);
    glutKeyboardFunc(KeyboardGL);
    glutReshapeFunc(ReshapeGL);

    // Setup initial GL State
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glClearDepth( 1.0f );

    glShadeModel( GL_SMOOTH );

    std::cout << "Initialise OpenGL: Success!" << std::endl;
}

void DisplayGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );                   // Clear the color buffer, and the depth buffer.

    switch ( g_eCurrentScene )
    {
    case ST_Scene1:
        {
            RenderScene1();
        }
        break;
    case ST_Scene2:
        {
            RenderScene2();
        }
        break;
    case ST_Scene3:
        {
            RenderScene3();
        }
        break;
    case ST_Scene4:
        {
            RenderScene4();
        }
        break;
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

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

/* Unused Mouse methods */
void MouseGL( int button, int state, int x, int y )
{

}

void MotionGL( int x, int y )
{

}

void ReshapeGL( int w, int h )
{
    std::cout << "ReshapGL( " << w << ", " << h << " );" << std::endl;

    if ( h == 0) // Prevent A Divide By Zero error
    {
        h = 1; // Making Height Equal One
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

// Draw 2D Prmitives
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

void drawS(){
    glColor3f( 1.0f, 0.0f, 0.0f );                                          // Set Color to red
    glutSolidCube(0.5);
    glColor3f( 0.0f, 0.0f, 0.0f );                                          // Set Color to black
    glutWireCube(0.5);
    
    glTranslatef( 0.5f, 0.0f, 0.0f );

    glColor3f( 1.0f, 0.0f, 0.0f );                                          // Set Color to red
    glutSolidCube(0.5);
    glColor3f( 0.0f, 0.0f, 0.0f );                                          // Set Color to black
    glutWireCube(0.5);

    glTranslatef( 0.0f, 0.5f, 0.0f );

    glColor3f( 1.0f, 0.0f, 0.0f );                                          // Set Color to red
    glutSolidCube(0.5);
    glColor3f( 0.0f, 0.0f, 0.0f );                                          // Set Color to black
    glutWireCube(0.5);

    glTranslatef( 0.5f, 0.0f, 0.0f );

    glColor3f( 1.0f, 0.0f, 0.0f );                                          // Set Color to red
    glutSolidCube(0.5);
    glColor3f( 0.0f, 0.0f, 0.0f );                                          // Set Color to black
    glutWireCube(0.5);

}

void RenderScene1()
{

    glMatrixMode( GL_MODELVIEW );                                           // Switch to modelview matrix mode
    glLoadIdentity();                                                       // Load the identity matrix

    // float x = .5; /* Centre in the middle of the window */
    // glRasterPos2f(x - (float) glutGet(GLUT_SCREEN_WIDTH) / 2, 0.);
    // glColor3f(1.f, 0.f, 0.f);
    // int len = strlen(hello_string);
    // for (int i = 0; i < len; i++) {
    //     glutBitmapCharacter(GLUT_BITMAP_8_BY_13, hello_string);
    // }

    glTranslatef( -1.5f, 1.0f, -6.0f );                                     // Translate our view matrix back and a bit to the left.
    
    
    drawS();
    // glColor3f( 1.0f, 0.0f, 0.0f );                                          // Set Color to red
    // // DrawTriangle( float2(0.0f, 1.0f), float2(-1.0f, -1.0f), float2(1.0f, -1.0f ) );
    // glutSolidCube(1);
    // glColor3f( 0.0f, 0.0f, 0.0f );                                          // Set Color to black
    // glutWireCube(1);

    glTranslatef( 3.0f, 0.0f, 0.0f );                                       // Shift view 3 units to the right
    glColor3f( 0.0f, 0.0f, 1.0f );                                          // Set Color to blue
    // DrawRectangle( 2.0f, 2.0f );
    glutSolidCube(0.5);

    glTranslatef( -1.5f, -3.0f, 0.0f );                                     // Back to center and lower screen
    glColor3f( 1.0f, 1.0f, 0.0f );                                          // Set color to yellow
    DrawCircle( 1.0f, 16 );
}

void render_game_stage(){

    glColor3f( 1.0f, 1.0f, 1.0f);

    // Bottom
    glBegin( GL_QUADS );
        for(GLfloat x0f=0; x0f<X_DIM;x0f++){
            for(GLfloat z0f=0; z0f<Z_DIM;z0f++){
                glVertex3f(  x0f, 0.0f, z0f );                                   
                glVertex3f(  x0f+1.0f, 0.0f, z0f );
                glVertex3f(  x0f+1.0f, 0.0f, z0f+1.0f );                             
                glVertex3f(  x0f, 0.0f, z0f+1.0f );   
            }
        }
    glEnd();

    // Left
    glBegin( GL_QUADS );
        for(GLfloat y0f=0; y0f<Y_DIM;y0f++){
            for(GLfloat z0f=0; z0f<Z_DIM;z0f++){
                glVertex3f(  0.0f, y0f, z0f );                                   
                glVertex3f(  0.0f, y0f, z0f+1.0f );
                glVertex3f(  0.0f, y0f+1.0f, z0f+1.0f );                             
                glVertex3f(  0.0f, y0f+1.0f, z0f );   
            }
        }
    glEnd();

    // Right
    glBegin( GL_QUADS );
        for(GLfloat y0f=0; y0f<Y_DIM;y0f++){
            for(GLfloat z0f=0; z0f<Z_DIM;z0f++){
                glVertex3f(  10.0f, y0f, z0f );                                   
                glVertex3f(  10.0f, y0f, z0f+1.0f );
                glVertex3f(  10.0f, y0f+1.0f, z0f+1.0f );                             
                glVertex3f(  10.0f, y0f+1.0f, z0f );   
            }
        }
    glEnd();

}

void render_cube(int x0, int y0, int z0, int color){
    
    GLfloat x0f=(GLfloat)x0, y0f=(GLfloat)y0, z0f=(GLfloat)z0;
    float r,g,b;
    r=color/100;
    g=(color/10)%10;
    b=color%10;


    glBegin( GL_QUADS );

        glColor3f( (GLfloat)r, (GLfloat)g, (GLfloat)b);

        // Top face
        glVertex3f(  x0f, y0f+1.0f, z0f );                                   
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f );
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f+1.0f );                             
        glVertex3f(  x0f, y0f+1.0f, z0f+1.0f );                                  

        // glColor3f(   1.0f, 1.0f,  0.0f ); // Yellow

        // Bottom face
        glVertex3f(  x0f, y0f, z0f );                                   
        glVertex3f(  x0f+1.0f, y0f, z0f );
        glVertex3f(  x0f+1.0f, y0f, z0f+1.0f );                             
        glVertex3f(  x0f, y0f, z0f+1.0f );         

        // Front face
        glVertex3f(  x0f, y0f, z0f+1.0f );                                   
        glVertex3f(  x0f, y0f+1.0f, z0f+1.0f );
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f+1.0f );                             
        glVertex3f(  x0f+1.0f, y0f, z0f+1.0f );  

        // Back face
        glVertex3f(  x0f, y0f, z0f );                                   
        glVertex3f(  x0f, y0f+1.0f, z0f );
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f );                             
        glVertex3f(  x0f+1.0f, y0f, z0f );   

        // Left face
        glVertex3f(  x0f, y0f, z0f );                                   
        glVertex3f(  x0f, y0f, z0f+1.0f );
        glVertex3f(  x0f, y0f+1.0f, z0f+1.0f );                             
        glVertex3f(  x0f, y0f+1.0f, z0f );   

        // Right face
        glVertex3f(  x0f+1.0f, y0f, z0f );                                   
        glVertex3f(  x0f+1.0f, y0f, z0f+1.0f );
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f+1.0f );                             
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f );      

    glEnd();

}

void RenderScene2()
{
    glMatrixMode( GL_MODELVIEW );                                           // Switch to modelview matrix mode
    glLoadIdentity();                                                       // Load the identity matrix

    glTranslatef( -5.0f, -10.0f, -30.0f );                                     // Translate back and to the left
    
    /* Rendering game matrix */
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    // glBegin( GL_QUADS );
    //     glColor3f( 1.0f, 1.0f, 1.0f ); // White

    //     glVertex3f( 0.0f, 0.0f, 0.0f);
    //     glVertex3f( 10.0f, 0.0f, 0.0f);
    //     glVertex3f( 10.0f, 0.0f, 10.0f);
    //     glVertex3f( 0.0f, 0.0f, 10.0f);
    // glEnd();

    // glBegin( GL_QUADS );
    //     glColor3f( 1.0f, 1.0f, 1.0f ); // White

    //     glVertex3f( 0.0f, 0.0f, 0.0f);
    //     glVertex3f( 0.0f, 0.0f, 10.0f);
    //     glVertex3f( 0.0f, 22.0f, 10.0f);
    //     glVertex3f( 0.0f, 22.0f, 0.0f);
    // glEnd();

    // glBegin( GL_QUADS );
    //     glColor3f( 1.0f, 1.0f, 1.0f ); // White

    //     glVertex3f( 10.0f, 0.0f, 0.0f);
    //     glVertex3f( 10.0f, 0.0f, 10.0f);
    //     glVertex3f( 10.0f, 22.0f, 10.0f);
    //     glVertex3f( 10.0f, 22.0f, 0.0f);
    // glEnd();

    // glBegin( GL_QUADS );
    //     glColor3f( 1.0f, 1.0f, 1.0f ); // White

    //     glVertex3f( 0.0f, 0.0f, 0.0f);
    //     glVertex3f( 10.0f, 0.0f, 0.0f);
    //     glVertex3f( 10.0f, 22.0f, 0.0f);
    //     glVertex3f( 0.0f, 22.0f, 0.0f);
    // glEnd();

    render_game_stage();

    /* Rendering the game cubes */

    Cube cube_aux;
    int color;
    int x,y,z;

    // glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    for (size_t i = 0; i < MATRIX_SIZE; i++){
            // std::cout << matrix->get_cubes()[i]; // << "\n";
            cube_aux = matrix->get_cubes()[i];
            color = cube_aux.get_color();
             
            x=id_to_x(i);
            y=id_to_y(i);
            z=id_to_z(i);

            if (cube_aux.is_occupied()){
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                // render_cube(x,y,z,111);
                // glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                render_cube(x,y,z,color);
            }
    }

}



void RenderScene3()
{
    glMatrixMode( GL_MODELVIEW );                                           // Switch to modelview matrix mode
    glLoadIdentity();                                                       // Load the identity matrix

    glTranslatef( -1.5f, 1.0f, -6.0f );                                     // Translate back and to the left
    glPushMatrix();                                                         // Push the current transformation onto the matrix stack
    glRotatef( g_fRotate1, 0.0f, 0.0f, 1.0f );
    // Draw a triangle with different colors on each vertex
    glBegin( GL_TRIANGLES );
        glColor3f( 1.0f, 0.0f, 0.0f );                                      // Red
        glVertex2f( 0.0f, 1.0f );                                           // Top-Center

        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex2f( -1.0f, -1.0f );                                         // Bottom-Left

        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex2f( 1.0f, -1.0f );                                          // Bottom-Right
    glEnd();
    glPopMatrix();

    glTranslatef( 3.0f, 0.0f, 0.0f );                                       // Translate right
    glPushMatrix();
    glRotatef( g_fRotate2, 0.0f, 0.0f, 1.0f );
    // Draw a rectangle with different colors on each vertex
    glBegin( GL_QUADS );
        glColor3f( 1.0f, 0.0f, 0.0f );                                      // Red
        glVertex2f( -1.0f, 1.0f );                                          // Top-Left

        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex2f( 1.0f, 1.0f );                                           // Top-Right

        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex2f( 1.0f, -1.0f );                                          // Bottom-Right

        glColor3f( 1.0f, 1.0f, 1.0f );                                      // White
        glVertex2f( -1.0f, -1.0f );                                         // Bottom-Left
    glEnd();
    glPopMatrix();

    glTranslatef( -1.5f, -3.0f, 0.0f );                                     // Back to center and lower screen
    glPushMatrix();
    glRotatef( g_fRotate3, 0.0f, 0.0f, 1.0f );
    // Draw a circle with blended red/blue vertecies
    const float step = M_PI / 16;
    const float radius = 1.0f;

    glBegin( GL_TRIANGLE_FAN );
        glColor3f( 1.0f, 1.0f, 1.0f );    
        glVertex2f(0.0f, 0.0f);
        for ( float angle = 0.0f; angle < ( 2.0f * M_PI ); angle += step )
        {
            float fSin = sinf(angle);
            float fCos = cosf(angle);

            glColor3f( ( fCos + 1.0f ) * 0.5f, ( fSin + 1.0f ) * 0.5f , 0.0f);
            glVertex2f( radius * fSin, radius * fCos );
        }
        glColor3f( 1.0f, 0.5f, 0.0f );
        glVertex2f( 0.0f, radius ); // One more vertex to close the circle
    glEnd();
    glPopMatrix();
}

void RenderScene4()
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_DEPTH_TEST );

    glTranslatef( -1.5f, 1.0f, -6.0f );                                     // Translate back and to the left

    glPushMatrix();                                                         // Push the current modelview matrix on the matrix stack
    // glRotatef(g_fRotate1, 1.0f, 1.0f, 1.0f );                               // Rotate on all 3 axis
    glBegin( GL_TRIANGLES );                                                // Draw a pyramid        
        glColor3f( 1.0f, 0.0f, 0.0f );                                      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f );                                     // Top of front face
        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex3f( -1.0f, -1.0f, 1.0f );                                   // Left of front face
        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex3f( 1.0f, -1.0f, 1.0f );                                    // Right of front face

        glColor3f( 1.0f, 0.0f, 0.0f );                                      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f );                                     // Top of right face
        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex3f( 1.0f, -1.0f, 1.0f );                                    // Left of right face
        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex3f( 1.0f, -1.0f, -1.0f );                                   // Right of right face

        glColor3f( 1.0f, 0.0f, 0.0f );                                      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f );                                     // Top of back face
        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex3f( 1.0f, -1.0f, -1.0f );                                   // Left of back face
        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex3f( -1.0f, -1.0f, -1.0f );                                  // Right of back face

        glColor3f( 1.0f, 0.0f, 0.0f );                                      // Red
        glVertex3f( 0.0f, 1.0f, 0.0f );                                     // Top of left face
        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex3f( -1.0f, -1.0f, -1.0f );                                  // Left of left face
        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex3f( -1.0f, -1.0f, 1.0f );                                   // Right of left face
    glEnd();

    // Render a quad for the bottom of our pyramid
    glBegin( GL_QUADS );
        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex3f( -1.0f, -1.0f, 1.0f );                                   // Left/right of front/left face
        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex3f( 1.0f, -1.0f, 1.0f );                                    // Right/left of front/right face
        glColor3f( 0.0f, 1.0f, 0.0f );                                      // Green
        glVertex3f( 1.0f, -1.0f, -1.0f );                                   // Right/left of right/back face
        glColor3f( 0.0f, 0.0f, 1.0f );                                      // Blue
        glVertex3f( -1.0f, -1.0f, -1.0f );                                  // Left/right of right/back face
    glEnd();
    glPopMatrix();

    glTranslatef( 3.0f, 0.0f, 0.0f );                                        // Translate right
    glPushMatrix();                                                         // Push the current modelview matrix on the matrix stack
    glRotatef( g_fRotate2, 1.0f, 1.0f, 1.0f );                              // Rotate the primitive on all 3 axis
    glBegin( GL_QUADS );
        // Top face
        glColor3f(   0.0f, 1.0f,  0.0f );                                   // Green
        glVertex3f(  1.0f, 1.0f, -1.0f );                                   // Top-right of top face
        glVertex3f( -1.0f, 1.0f, -1.0f );                                   // Top-left of top face
        glVertex3f( -1.0f, 1.0f,  1.0f );                                   // Bottom-left of top face
        glVertex3f(  1.0f, 1.0f,  1.0f );                                   // Bottom-right of top face

        // Bottom face
        glColor3f(   1.0f,  0.5f,  0.0f );                                  // Orange
        glVertex3f(  1.0f, -1.0f, -1.0f );                                  // Top-right of bottom face
        glVertex3f( -1.0f, -1.0f, -1.0f );                                  // Top-left of bottom face
        glVertex3f( -1.0f, -1.0f,  1.0f );                                  // Bottom-left of bottom face
        glVertex3f(  1.0f, -1.0f,  1.0f );                                  // Bottom-right of bottom face

        // Front face
        glColor3f(   1.0f,  0.0f, 0.0f );                                  // Red
        glVertex3f(  1.0f,  1.0f, 1.0f );                                  // Top-Right of front face
        glVertex3f( -1.0f,  1.0f, 1.0f );                                  // Top-left of front face
        glVertex3f( -1.0f, -1.0f, 1.0f );                                  // Bottom-left of front face
        glVertex3f(  1.0f, -1.0f, 1.0f );                                  // Bottom-right of front face

        // Back face
        glColor3f(   1.0f,  1.0f,  0.0f );                                 // Yellow
        glVertex3f(  1.0f, -1.0f, -1.0f );                                 // Bottom-Left of back face
        glVertex3f( -1.0f, -1.0f, -1.0f );                                 // Bottom-Right of back face
        glVertex3f( -1.0f,  1.0f, -1.0f );                                 // Top-Right of back face
        glVertex3f(  1.0f,  1.0f, -1.0f );                                 // Top-Left of back face

        // Left face
        glColor3f(   0.0f,  0.0f,  1.0f);                                   // Blue
        glVertex3f( -1.0f,  1.0f,  1.0f);                                   // Top-Right of left face
        glVertex3f( -1.0f,  1.0f, -1.0f);                                   // Top-Left of left face
        glVertex3f( -1.0f, -1.0f, -1.0f);                                   // Bottom-Left of left face
        glVertex3f( -1.0f, -1.0f,  1.0f);                                   // Bottom-Right of left face

        // Right face
        glColor3f(   1.0f,  0.0f,  1.0f);                                   // Violet
        glVertex3f(  1.0f,  1.0f,  1.0f);                                   // Top-Right of left face
        glVertex3f(  1.0f,  1.0f, -1.0f);                                   // Top-Left of left face
        glVertex3f(  1.0f, -1.0f, -1.0f);                                   // Bottom-Left of left face
        glVertex3f(  1.0f, -1.0f,  1.0f);                                   // Bottom-Right of left face
    glEnd();
    glPopMatrix();

    glTranslatef( -1.5f, -3.0f, 0.0f );                                     // Back to center and lower screen
    glPushMatrix();
    glRotatef( g_fRotate3, 1.0f, 1.0f, 1.0f );   
    glColor3f( 1.0f, 1.0f, 0.0f );                                          // Yellow
    glutSolidSphere( 1.0f, 16, 16 );                                        // Use GLUT to draw a solid sphere
    glScalef( 1.01f, 1.01f, 1.01f );                                        
    glColor3f( 1.0f, 0.0f, 0.0f );                                          // Red
    glutWireSphere( 1.0f, 16, 16 );                                         // Use GLUT to draw a wireframe sphere
    glPopMatrix();
}


int id_to_x(int id){
    int x;

    x=id%10;
    return x;
}

int id_to_y(int id){
    int y;

    y=(int)id/100;
    return y;
}

int id_to_z(int id){
    int z;

    z=(int)id/10;
    z=z%10;
    return z;
}