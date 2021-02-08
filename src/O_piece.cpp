#include "Piece.h"
#include "Cube.h"
#include "O_piece.h"

O_piece::O_piece()
{
    m_color=110; // Yellow
    m_cube_position[0]=2044;
    m_cube_position[1]=m_cube_position[0]+100;
    m_cube_position[3]=m_cube_position[0]+1;
    m_cube_position[2]=m_cube_position[1]+1;
    // std::cout << "Creating O_piece\n";
}

void O_piece::rotate_x(int* new_pos){

    new_pos[0]=m_cube_position[0];
    new_pos[1]=m_cube_position[1]-110;
    new_pos[2]=m_cube_position[2]-110;
    new_pos[3]=m_cube_position[3];
};

void O_piece::rotate_z(int* new_pos){    

    new_pos[0]=m_cube_position[0];
    new_pos[1]=m_cube_position[0]+1;
    new_pos[2]=m_cube_position[2]-99;
    new_pos[3]=m_cube_position[0]-100;
}

void O_piece::rotate_y(int* new_pos){

    new_pos[0]=m_cube_position[0];
    new_pos[1]=m_cube_position[1];
    new_pos[2]=m_cube_position[2]-9;
    new_pos[3]=m_cube_position[3]-9;

}