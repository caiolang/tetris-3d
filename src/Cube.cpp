#include "Cube.h"


Cube::Cube(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_occupied = false;
}

Cube::Cube(int pos_x, int pos_y, int pos_z) //Constructor 
{ 
    m_x = pos_x;
    m_y = pos_y;
    m_z = pos_z;
    m_occupied = false;
}

Cube::Cube(int pos_x, int pos_y, int pos_z, bool occ) //Constructor 
{ 
    m_x = pos_x;
    m_y = pos_y;
    m_z = pos_z;
    m_occupied = occ;
}

// Acess methods
int Cube::get_x()  { return m_x; }
int Cube::get_y()  { return m_y; }
int Cube::get_z()  { return m_z; }
bool Cube::is_occupied()  { return m_occupied; }


void Cube::print(std::ostream &flux) const
{
    // flux << m_heures << "h" << m_minutes << "m" << m_secondes << "s";
    flux << "( " << m_x << ", " << m_y << ", " << m_z << ", " << m_occupied << " )";
}

std::ostream &operator<<( std::ostream &flux, Cube const& cube)
{
    cube.print(flux) ;
    return flux;
}
