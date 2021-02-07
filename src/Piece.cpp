#include "Piece.h"
#include "Cube.h"

Piece::Piece(){
    stop= false;
}

int* Piece::get_cubes(){
    return cube_position;
}

bool Piece::get_stop(){
    return stop;
}

char* Piece::get_color(){
    return color;
}

void Piece::translate_x(int* new_pos, int dir){
    int step=1;
    if (dir<0){step=-1;}
    for(int i=0; i<4; i++){
        new_pos[i]=cube_position[i]+step;
    }
}

void Piece::translate_y(int* new_pos){
    for(int i=0; i<4; i++){
        new_pos[i]=cube_position[i]-100;
    }
}

void Piece::translate_z(int* new_pos,int dir){
    int step=1;
    if (dir<0){step=-1;}
    for(int i=0; i<4; i++){
        new_pos[i]=cube_position[i]+10*step;
    }
}