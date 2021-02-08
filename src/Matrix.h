#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include "Cube.h"
 
class Matrix
{
    
    private:

        // int m_cubes[2200];
        Cube m_cubes[2200];

    public:
    
        Matrix(); // Simple constructor
        int coord_to_id(int x, int y, int z);
        int id_to_x(int id);
        int id_to_y(int id);
        int id_to_z(int id);
        bool is_safe(int* ids_vec); // Receives a vector of four elements


        // Matrix(int x_dim, int y_dim, int z_dim); // Constructor with matrix dimensions

        // int* get_cubes();    
        Cube* get_cubes();

};
 
#endif