#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Cube.h"
#include "O_piece.h"
#include "I_piece.h"
#include "S_piece.h"
#include "Z_piece.h"
#include "T_piece.h"
#include "L_piece.h"
#include "J_piece.h"
#include "Piece.h"
 
class Matrix
{
    
    private:

        Cube m_cubes[2200];
        // std::vector<Piece*> m_pieces;
        Piece* m_curr_piece;
        Piece* m_next_piece;

        Piece* m_curr_ghost;
        Piece* m_next_ghost;

    public:
    
        Matrix(); // Default constructor
        int coordToId(int x, int y, int z);
        int idToX(int id);
        int idToY(int id);
        int idToZ(int id);
        bool isFree(int* ids_vec); // Receives a vector of four elements
        bool isSafeToMove(int a0,int a1,int a2,int a3,int b0,int b1,int b2,int b3);
        // void setAsPiece(int* ids_vec, int color); // Receives a vector of four elements and a color
        // void setAsEmpty(int* ids_vec);

        void setAsPiece(int id0, int id1, int id2, int id3, int color);
        void setAsEmpty(int id0, int id1, int id2, int id3);
        void setAsGhost(int id0, int id1, int id2, int id3, int color);
        void setAsNonGhost(int id0, int id1, int id2, int id3);

        // void initPiece(int piece_id);
        void initCurrPiece();
        void initGhostPiece();
        void nextPiece();
        void updateGhostPiece();

        void rotatePieceX();
        void rotatePieceY();
        void rotatePieceZ();

        void translatePieceX(int amount);
        void translatePieceY(int amount);
        bool autoTranslateCurrY();
        bool autoTranslateGhostY();
        void translatePieceZ(int amount);

        int getFreeDeltaY();
        

        Cube* getCubes();


};
 
#endif