#include "Piece.h"
#include "Cube.h"
#include "S_piece.h"

S_piece::S_piece()
{
    m_color=10; // Green
    m_cube_position[0]=2044;
    m_cube_position[1]=m_cube_position[0]+1;
    m_cube_position[2]=m_cube_position[1]+100;
    m_cube_position[3]=m_cube_position[2]+1;
}