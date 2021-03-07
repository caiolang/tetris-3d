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

        bool getStop();
        int* getCubes();
        int getColor();

        void translateX(int amount);
        void translateY(int amount);
        void translateZ(int amount);

        void rotateX();
        void rotateY();
        void rotateZ();
        void setCubesPos(int pos0,int pos1,int pos2,int pos3);

};   

 
#endif