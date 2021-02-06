#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <iostream>
 
class Cube{
    private:
        int x;
        int y;
        int z;
        bool occupied;
        // Piece *piece
    
    public:
        Cube(int pos_x, int pos_y, int pos_z, bool occ);
    
        int get_x();
        int get_y();
        int get_z();
        bool is_occupied();
};
 
#endif