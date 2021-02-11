#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include "Cube.h"
#include "O_piece.h"
 
class Matrix
{
    
    private:

        Cube m_cubes[2200];
        std::vector<Piece*> m_pieces;

    public:
    
        Matrix(); // Default constructor
        int coordToId(int x, int y, int z);
        int idToX(int id);
        int idToY(int id);
        int idToZ(int id);
        bool isSafe(int* ids_vec); // Receives a vector of four elements
        void setAsPiece(int* ids_vec, int color); // Receives a vector of four elements and a color
        void initPiece(int piece_id);
        void rotatePieceX(int piece_id, int newPos[]);

        Cube* getCubes();

};
 
#endif