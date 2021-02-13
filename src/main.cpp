#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string.h>
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

/* GLUT constants */
int g_iWindowWidth = 512;
int g_iWindowHeight = 512;
int g_iGLUTWindowHandle = 0;
int g_iErrorCode = 0;

/* Tetris constants */
const int MATRIX_SIZE = 2200;
const int X_DIM = 10;
const int Y_DIM = 22;
const int Z_DIM = 10;
const int NUM_PIECES = 20;

Matrix *matrix = new Matrix();

/* GL functions' primitives */
void InitGL( int argc, char* argv[] );
void DisplayGL();
void IdleGL();
void KeyboardGL( unsigned char c, int x, int y );
void MouseGL( int button, int state, int x, int y );
void MotionGL( int x, int y );
void ReshapeGL( int w, int h );
void printTxt(float x, float y, char *String);

/* 3D Primitives */
void DrawCube( float width, float height, float depth );
void DrawSphere( float radius );
void DrawPyramid( float scale = 1.0f );

/* Added functions */
int idToX(int id);
int idToY(int id);
int idToZ(int id);
void resetFlags();
void makeMove(int piece_id);

enum ESceneType
{
    ST_Scene1 = 0,
    ST_Scene2
};
ESceneType g_eCurrentScene = ST_Scene1;


float time_sum = 0.0f;
int level = 0;
int points = 0;

/* Clock variables */
std::clock_t g_PreviousTicks;
std::clock_t g_CurrentTicks;

// Render main menu
void RenderScene1();
// Render Tetris Game
void RenderScene2(); 


// We're exiting, cleanup the allocated resources.
void Cleanup( int exitCode, bool bExit = true );

// ------------------------------------------------

int main( int argc, char* argv[] )
{
    // Capture the previous time to calculate the delta time on the next frame
    g_PreviousTicks = std::clock();

    matrix->initCurrPiece();


    InitGL( argc, argv );
    glutMainLoop();
    Cleanup(g_iErrorCode);
}

// void startPiece(Piece *piece){
//     // std::cout << "Starting piece " + piece + "\n";
//     // Cube* cubes;
//     int color;
//     int *id;

//     id = piece->getCubes();
//     matrix[id]
//     color = piece->getColor();

//     for(int i=0; i<4; i++){
//         cubes[i].setColor(color);
//         cubes[i].setOccupied(true);
//         std::cout << "Cube in position " + piece + "\n";
//     }

// }

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
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
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
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void IdleGL()
{   
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
            // glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );                         // White background
            glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );                         // Black background
            g_eCurrentScene = ST_Scene1;
        }
        break;
    case '2':
        {
            glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );                         // Black background
            g_eCurrentScene = ST_Scene2;
        }
        break;
    case 'i':
    case 'I':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->rotatePieceX();
            }

        }
        break;
    case 'o':
    case 'O':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->rotatePieceY();
            }
        }
        break;
    case 'p':
    case 'P':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->rotatePieceZ();
            }
        }
        break;
    case 'd':
    case 'D':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->translatePieceX(1);
            }

        }
        break;
    case 'a':
    case 'A':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->translatePieceX(-1);
            }

        }
        break;
    case 'w':
    case 'W':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->translatePieceZ(-1);
            }
        }
        break;
    case 's':
    case 'S':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->translatePieceZ(1);
            }
        }
        break;
    case 'e':
    case 'E':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->translatePieceY(1);
            }
        }
        break;
    case 'q':
    case 'Q':
        {
            if(g_eCurrentScene==ST_Scene2){
                matrix->translatePieceY(-1);
            }
        }
        break;

    case '\033': // escape quits
    // case '\015': // Enter quits    
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

void printTxt(float x, float y, char *String)
{
    /* Available fonts: */
    // GLUT_BITMAP_8_BY_13
    // GLUT_BITMAP_9_BY_15
    // GLUT_BITMAP_TIMES_ROMAN_10
    // GLUT_BITMAP_TIMES_ROMAN_24
    // GLUT_BITMAP_HELVETICA_10
    // GLUT_BITMAP_HELVETICA_12
    // GLUT_BITMAP_HELVETICA_18

    char *c;

    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 10);

    glColor3f(255.0f, 255.0f, 255.0f);
    glRasterPos2f(x, y);
    glDisable(GL_LIGHTING);

    for (c = String; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
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

void RenderScene1()
{

    glMatrixMode( GL_MODELVIEW );                                           // Switch to modelview matrix mode
    glLoadIdentity();       

    char scr[30];
    strcpy(scr, "T E T R I S  3 D");
    printTxt(5.0f, 5.0f, scr);
    strcpy(scr, "rafaverissimo e caiolang");
    printTxt(5.0f, 7.0f, scr);

    // glMatrixMode( GL_MODELVIEW );                                           // Switch to modelview matrix mode
    // glLoadIdentity();                                                       // Load the identity matrix

    // // float x = .5; /* Centre in the middle of the window */
    // // glRasterPos2f(x - (float) glutGet(GLUT_SCREEN_WIDTH) / 2, 0.);
    // // glColor3f(1.f, 0.f, 0.f);
    // // int len = strlen(hello_string);
    // // for (int i = 0; i < len; i++) {
    // //     glutBitmapCharacter(GLUT_BITMAP_8_BY_13, hello_string);
    // // }

    // glTranslatef( -1.5f, 1.0f, -6.0f );                                     // Translate our view matrix back and a bit to the left.
    

    // glTranslatef( 3.0f, 0.0f, 0.0f );                                       // Shift view 3 units to the right
    // glColor3f( 0.0f, 0.0f, 1.0f );                                          // Set Color to blue
    // // DrawRectangle( 2.0f, 2.0f );
    // glutSolidCube(0.5);

}

void renderGameStage(){

    // glColor3f( 1.0f, 1.0f, 1.0f);
    glColor3f( 0.3f, 0.3f, 0.3f);

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

    // Back
    glBegin( GL_QUADS );
        for(GLfloat y0f=0; y0f<Y_DIM;y0f++){
            for(GLfloat x0f=0; x0f<X_DIM;x0f++){
                glVertex3f(  x0f, y0f, 0.0f );                                   
                glVertex3f(  x0f, y0f+1.0f, 0.0f );
                glVertex3f(  x0f+1.0f, y0f+1.0f, 0.0f );                             
                glVertex3f(  x0f+1.0f, y0f, 0.0f );   
            }
        }
    glEnd();

      

}

void renderCube(int x0, int y0, int z0, int color){
    
    GLfloat x0f=(GLfloat)x0, y0f=(GLfloat)y0, z0f=(GLfloat)z0;
    float r,g,b;
    r=color/100;
    g=(color/10)%10;
    b=color%10;

    glBegin( GL_QUADS );

        // glColor3f( (GLfloat)r, (GLfloat)g, (GLfloat)b);
        glColor3f( (GLfloat)r-0.5f, (GLfloat)g-0.5f, (GLfloat)b-0.5f);

        // Top face
        glVertex3f(  x0f, y0f+1.0f, z0f );                                   
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f );
        glVertex3f(  x0f+1.0f, y0f+1.0f, z0f+1.0f );                             
        glVertex3f(  x0f, y0f+1.0f, z0f+1.0f );                                  

        // Bottom face
        glVertex3f(  x0f, y0f, z0f );                                   
        glVertex3f(  x0f+1.0f, y0f, z0f );
        glVertex3f(  x0f+1.0f, y0f, z0f+1.0f );                             
        glVertex3f(  x0f, y0f, z0f+1.0f );         

        glColor3f( (GLfloat)r-0.3f, (GLfloat)g-0.3f, (GLfloat)b-0.3f);

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

        glColor3f( (GLfloat)r, (GLfloat)g, (GLfloat)b);

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

    glEnd();

}

void renderGameText(){
    char scr[20];
    strcpy(scr, "N E X T  P I E C E:");
    printTxt(7.3f, 7.0f, scr);

    strcpy(scr, "L E V E L:");
    printTxt(7.3f, 5.5f, scr);
    sprintf(scr, "%d", level);
    printTxt(7.3f, 3.7f, scr);

    strcpy(scr, "P O I N T S:");
    printTxt(7.3f, 4.0f, scr);
    sprintf(scr, "%d", points);
    printTxt(7.3f, 3.7f, scr);
}

void RenderScene2()
{

    g_CurrentTicks = std::clock();
    float deltaTicks = ( g_CurrentTicks - g_PreviousTicks );
    g_PreviousTicks = g_CurrentTicks;

    float fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;
    time_sum += fDeltaTime;
    // std::cout<<time_sum;
    if(time_sum>0.01){
        matrix->translatePieceY(-1);
        time_sum=0;
    }

    renderGameText();

    glMatrixMode( GL_MODELVIEW ); // Switch to modelview matrix mode
    glLoadIdentity(); // Load the identity matrix
    glEnable( GL_DEPTH_TEST );
    glTranslatef( -5.0f, -10.0f, -30.0f ); // 
    
    /* Rendering game matrix */
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    renderGameStage();

    /* Rendering the game cubes */
    Cube cube_aux;
    int color;
    int x,y,z;

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    for (size_t i = 0; i < MATRIX_SIZE; i++){
            cube_aux = matrix->getCubes()[i];
            color = cube_aux.getColor();
             
            x=idToX(i);
            y=idToY(i);
            z=idToZ(i);

            if (cube_aux.isOccupied()){
                renderCube(x,y,z,color);
            }
    }

    

}




int idToX(int id){
    int x;

    x=id%10;
    return x;
}

int idToY(int id){
    int y;

    y=(int)id/100;
    return y;
}

int idToZ(int id){
    int z;

    z=(int)id/10;
    z=z%10;
    return z;
}

