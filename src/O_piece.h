#ifndef O_PIECE_H
#define O_PIECE_H

#include <vector>
#include <iostream>
#include "Piece.h"
#include "Cube.h"

class O_piece : public Piece{
    public:
        O_piece();
        using Piece::rotate_x;
        virtual void rotate_x(int* new_pos);
        using Piece::rotate_y;
        virtual void rotate_y(int* new_pos);
        using Piece::rotate_z;
        virtual void rotate_z(int* new_pos);
};





#endif