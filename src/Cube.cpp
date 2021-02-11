#include "Cube.h"

Cube::Cube(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_occupied = false;
    m_color = 101; // DEFAULT: Violet (TEMPORARY)
    // m_piece = NULL; 
}

Cube::Cube(int pos_x, int pos_y, int pos_z) //Constructor 
{ 
    m_x = pos_x;
    m_y = pos_y;
    m_z = pos_z;
    m_occupied = false;
    m_color = 101; // DEFAULT: Violet (TEMPORARY)
    // m_piece = NULL;
}

Cube::Cube(int pos_x, int pos_y, int pos_z, bool occ) //Constructor 
{ 
    m_x = pos_x;
    m_y = pos_y;
    m_z = pos_z;
    m_occupied = occ;
    m_color = 101; // DEFAULT: Violet (TEMPORARY)
    // m_piece = NULL;

    //TEMPORARY:
    // if(pos_x==3){
    //     m_occupied=true;
    // }

    // if(pos_x==6 && pos_y==4 && pos_z==3 ){
    //     m_occupied=true;
    // }


    // if(pos_x==4 && pos_y==20 && pos_z==0 ){
    //     m_occupied=true;
    // }

    // if(pos_x==3 && pos_y==20 && pos_z==4 ){
    //     m_occupied=true;
    // }

    // if(pos_x==5 && pos_y==19 && pos_z==4 ){
    //     m_occupied=true;
    // }

    // if(pos_x==5 && pos_y==20 && pos_z==4 ){
    //     m_occupied=true;
    // }

}

// Acess methods
int Cube::getX()  { return m_x; }
int Cube::getY()  { return m_y; }
int Cube::getZ()  { return m_z; }
int Cube::getPos() {return m_x+10*m_z+100*m_y;}
bool Cube::isOccupied()  { return m_occupied; }
int Cube::getColor() { return m_color;} // TEMPORARY

void Cube::setColor(int color){
    this->m_color = color;
}

void Cube::setOccupied(bool state){
    this->m_occupied = state;
}

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
