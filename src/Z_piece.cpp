#include "Piece.h"
#include "Cube.h"
#include "Z_piece.h"

Z_piece::Z_piece()
{
    m_color=100; // Red
    m_cube_position[0]=2144;
    m_cube_position[1]=m_cube_position[0]+1;
    m_cube_position[2]=m_cube_position[1]-100;
    m_cube_position[3]=m_cube_position[2]+1;
}

