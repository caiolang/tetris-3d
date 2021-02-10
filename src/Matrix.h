#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include "Cube.h"
#include "O_piece.h"
 
class Matrix
{
    
    private:

        Cube m_cubes[2200];
        std::vector<Piece*> m_pieces;

    public:
    
        Matrix(); // Default constructor
        int coord_to_id(int x, int y, int z);
        int id_to_x(int id);
        int id_to_y(int id);
        int id_to_z(int id);
        bool is_safe(int* ids_vec); // Receives a vector of four elements
        void set_as_piece(int* ids_vec, int color); // Receives a vector of four elements and a color
        void initialize_piece(int piece_id);
        void rotate_piece_x(int piece_id, int newPos[]);

        Cube* get_cubes();

};
 
#endif