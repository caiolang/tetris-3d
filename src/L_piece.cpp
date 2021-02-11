#include "Piece.h"
#include "Cube.h"
#include "L_piece.h"

L_piece::L_piece() 
{
    m_color=111; // White
    m_cube_position[0]=2044;
    m_cube_position[1]=m_cube_position[0]+100;
    m_cube_position[2]=m_cube_position[1]+1;
    m_cube_position[3]=m_cube_position[2]+1;
    // std::cout << "Creating O_piece\n";
}

