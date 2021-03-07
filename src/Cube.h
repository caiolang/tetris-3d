#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include "Piece.h"
 
class Cube{
    private:

        int m_x;
        int m_y;
        int m_z;
        bool m_occupied;
        bool m_ghost;
        int m_color; 
        
    
    public:
        Cube(); // Default constructor 
        Cube(int pos_x, int pos_y, int pos_z); //Constructor 
        Cube(int pos_x, int pos_y, int pos_z, bool occ); //Constructor 
    
        int getX() ;
        int getY() ;
        int getZ() ;
        int getPos() ;
        bool isOccupied() ;
        bool isGhost() ;
        
        int getColor(); 

        void setColor(int color);
        void setOccupied(bool state);
        void setGhost(bool state);

        void print(std::ostream &flux) const;      
};

std::ostream &operator<<( std::ostream &flux, Cube const& cube);
 
#endif