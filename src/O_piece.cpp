#include "Piece.h"
#include "Cube.h"
#include "O_piece.h"

O_piece::O_piece()
{
    color="yellow";
    cube_position[0]=2044;
    cube_position[1]=cube_position[0]+100;
    cube_position[3]=cube_position[0]+1;
    cube_position[2]=cube_position[1]+1;
}

void O_piece::rotate_x(int* new_pos){

    new_pos[0]=cube_position[0];
    new_pos[1]=cube_position[1]-110;
    new_pos[2]=cube_position[2]-110;
    new_pos[3]=cube_position[3];
};

void O_piece::rotate_z(int* new_pos){    

    new_pos[0]=cube_position[0];
    new_pos[1]=cube_position[0]+1;
    new_pos[2]=cube_position[2]-99;
    new_pos[3]=cube_position[0]-100;
}

void O_piece::rotate_y(int* new_pos){

    new_pos[0]=cube_position[0];
    new_pos[1]=cube_position[1];
    new_pos[2]=cube_position[2]-9;
    new_pos[3]=cube_position[3]-9;

}