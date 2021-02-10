#include "Piece.h"
#include "Cube.h"
#include "T_piece.h"

T_piece::T_piece() 
{
    m_color=101; // Purple
    m_cube_position[2]=2144;
    m_cube_position[1]=m_cube_position[2]-100;
    m_cube_position[0]=m_cube_position[1]-1;
    m_cube_position[3]=m_cube_position[1]+1;
    // std::cout << "Creating O_piece\n";
}

