#include "Piece.h"
#include "Cube.h"
#include "J_piece.h"

J_piece::J_piece() 
{
    m_color=1; // Blue
    m_cube_position[0]=2144;
    m_cube_position[1]=m_cube_position[0]-100;
    m_cube_position[2]=m_cube_position[1]+1;
    m_cube_position[3]=m_cube_position[2]+1;
}

