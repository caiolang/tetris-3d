#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <iostream>
 
class Cube{
    private:

        int m_x;
        int m_y;
        int m_z;
        bool m_occupied;
        // Piece *piece
    
    public:
        Cube(); // Default constructor 
        Cube(int pos_x, int pos_y, int pos_z); //Constructor 
        Cube(int pos_x, int pos_y, int pos_z, bool occ); //Constructor 
    
        int get_x() ;
        int get_y() ;
        int get_z() ;
        bool is_occupied() ;

        void print(std::ostream &flux) const;      
};

std::ostream &operator<<( std::ostream &flux, Cube const& cube);
 
#endif