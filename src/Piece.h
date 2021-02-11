#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>

class Piece
{
    protected:
        int m_cube_position[4];
        bool m_stop;
        int m_color;

    public:
        Piece(); // Constructor
        void translateX(int* new_pos, int dir);
        void translateY(int* new_pos);
        void translateZ(int* new_pos,int dir);
        bool getStop();
        int* getCubes();
        int getColor();
        // void rotateX(int* new_pos);
        void rotateX(int new_pos[]);
        void rotateY(int* new_pos);
        void rotateZ(int* new_pos);

};   

 
#endif