#include "Piece.h"
#include "Cube.h"
#include "I_piece.h"

I_piece::I_piece() 
{
    m_color=011; // Cyan
    m_cube_position[0]=2144;
    m_cube_position[1]=m_cube_position[0]+1;
    m_cube_position[2]=m_cube_position[1]+1;
    m_cube_position[3]=m_cube_position[2]+1;
    // std::cout << "Creating O_piece\n";
}

