#ifndef GAME_H
#define GAME_H

// #define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>
#include <vector>
// #include <string.h>
#include "Cube.h"
#include "Matrix.h"
#include "Piece.h"
#include "O_piece.h"

// #ifdef __APPLE__
// #include <GLUT/glut.h>
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
// #else
// #include <GL/glut.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
// #endif

class Game {

    private:

    int g_iWindowWidth = 512;
    int g_iWindowHeight = 512;
    int g_iGLUTWindowHandle = 0;
    int g_iErrorCode = 0;

    const int MATRIX_SIZE = 2200;
    const int X_DIM = 10;
    const int Y_DIM = 22;
    const int Z_DIM = 10;
    const int NUM_PIECES = 20;

    Matrix *matrix = new Matrix();

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

    // Added functions
    int idToX(int id);
    int idToY(int id);
    int idToZ(int id);
    void startPiece(Piece *piece);

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

}

#endif
