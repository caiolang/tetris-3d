#include "Cube.h"

Cube::Cube(int pos_x, int pos_y, int pos_z, bool occ) //Constructor with parameters
{ 
    x = pos_x;
    y = pos_y;
    z = pos_z;
    occupied = occ;
}

// Acess methods
int Cube::get_x() { return x; }
int Cube::get_y() { return y; }
int Cube::get_z() { return z; }
bool Cube::is_occupied() { return occupied; }
