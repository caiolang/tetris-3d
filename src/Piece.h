#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>
#include "Cube.h"

class Piece
{
    protected:
        int cube_position[4];
        bool stop;
        char* color;

    public:
        Piece(); // Constructor
        void translate_x(int* new_pos, int dir);
        void translate_y(int* new_pos);
        void translate_z(int* new_pos,int dir);
        bool get_stop();
        int* get_cubes();
        char* get_color();
        void rotate_x(int* new_pos);
        void rotate_y(int* new_pos);
        void rotate_z(int* new_pos);
};   

 
#endif