#include "Cube.h"

Cube::Cube(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_occupied = false;
    m_ghost = false;
    m_color = 101; // DEFAULT: Violet
}

Cube::Cube(int pos_x, int pos_y, int pos_z) //Constructor 
{ 
    m_x = pos_x;
    m_y = pos_y;
    m_z = pos_z;
    m_occupied = false;
    m_ghost = false;
    m_color = 101; // DEFAULT: Violet
}

Cube::Cube(int pos_x, int pos_y, int pos_z, bool occ) //Constructor 
{ 
    m_x = pos_x;
    m_y = pos_y;
    m_z = pos_z;
    m_occupied = occ;
    m_ghost = false;
    m_color = 101; // DEFAULT: Violet
    
}

// Acess methods
int Cube::getX()  { return m_x; }
int Cube::getY()  { return m_y; }
int Cube::getZ()  { return m_z; }
int Cube::getPos() {return m_x+10*m_z+100*m_y;}
bool Cube::isOccupied()  { return m_occupied; }
bool Cube::isGhost()  { return m_ghost; }
int Cube::getColor() { return m_color;} 

void Cube::setColor(int color){
    this->m_color = color;
}

void Cube::setOccupied(bool state){
    this->m_occupied = state;
}

void Cube::setGhost(bool state){
    this->m_ghost = state;
}

void Cube::print(std::ostream &flux) const
{
    flux << "( " << m_x << ", " << m_y << ", " << m_z << ", " << m_occupied << " )";
}

std::ostream &operator<<( std::ostream &flux, Cube const& cube)
{
    cube.print(flux) ;
    return flux;
}
