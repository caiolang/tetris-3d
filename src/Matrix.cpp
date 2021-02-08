#include "Matrix.h"

Matrix::Matrix()
{
    // std::cout << "GOT INTO CONSTRUCTOR\n";

    /* Initializing the Matrix Cubes */
    for (int i = 0; i < 2200; i++)
    {
        m_cubes[i]= Cube(id_to_x(i), id_to_y(i), id_to_z(i), false);
    }
    

}

int Matrix::coord_to_id(int x, int y, int z){
    int id = x + 10*y + 100*z;
    return id;
}

int Matrix::id_to_x(int id){
    int x;

    x=id%10;
    return x;
}

int Matrix::id_to_y(int id){
    int y;

    y=(int)id/100;
    return y;
}

int Matrix::id_to_z(int id){
    int z;

    z=(int)id/10;
    z=z%10;
    return z;
}

Cube* Matrix::get_cubes(){
    return m_cubes;
}

