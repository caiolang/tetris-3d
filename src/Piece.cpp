#include "Piece.h"
#include "Cube.h"

Piece::Piece(){
    m_stop= false;
    m_color= 100; // DEFAULT: White (TEMPORARY)
}

int* Piece::get_cubes(){
    return m_cube_position;
}

bool Piece::get_stop(){
    return m_stop;
}

int Piece::get_color(){
    return m_color;
}

void Piece::translate_x(int* new_pos, int dir){
    int step=1;
    if (dir<0){step=-1;}
    for(int i=0; i<4; i++){
        new_pos[i]=m_cube_position[i]+step;
    }
}

void Piece::translate_y(int* new_pos){
    for(int i=0; i<4; i++){
        new_pos[i]=m_cube_position[i]-100;
    }
}

void Piece::translate_z(int* new_pos,int dir){
    int step=1;
    if (dir<0){step=-1;}
    for(int i=0; i<4; i++){
        new_pos[i]=m_cube_position[i]+10*step;
    }
}