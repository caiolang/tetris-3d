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
}

