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
        int m_color; // TEMPORARY - three digit (0-111) representing RGB color
    
    public:
        Cube(); // Default constructor 
        Cube(int pos_x, int pos_y, int pos_z); //Constructor 
        Cube(int pos_x, int pos_y, int pos_z, bool occ); //Constructor 
    
        int get_x() ;
        int get_y() ;
        int get_z() ;
        int get_pos() ;
        bool is_occupied() ;
        int get_color(); // TEMPORARY

        void print(std::ostream &flux) const;      
};

std::ostream &operator<<( std::ostream &flux, Cube const& cube);
 
#endif