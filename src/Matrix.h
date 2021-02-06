#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include "Cube.h"
 
class Matrix
{
    public:
 
    Matrix(); // Simple constructor
    int coordToId(int x, int y, int z);
    int idToX(int id);
    int idToY(int id);
    int idToZ(int id);

    // Matrix(int x_dim, int y_dim, int z_dim); // Constructor with matrix dimensions
    
    int* getCubes();
 
    private:

    int x,y,z;
    int cubes[2200];



};
 
#endif