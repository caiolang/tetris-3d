#include "Matrix.h"

Matrix::Matrix()
{
    std::cout << "GOT INTO CONSTRUCTOR\n";

    for (int i = 0; i < 2200; i++)
    {
        cubes[i]=3;
    }
    

}

int Matrix::coordToId(int x, int y, int z){
    int id = x + 10*y + 100*z;
    return id;
}

int Matrix::idToX(int id){
    int x;

    x=id%10;
    return x;
}

int Matrix::idToY(int id){
    int y;

    y=(int)id/10;
    y=y%10;
    return y;
}

int Matrix::idToZ(int id){
    int x;

    z=(int)id/100;
    return z;
}

int* Matrix::getCubes(){
    return cubes;
}

// ? Matrix::idToCoord(int id){
//     int x,y,z;

//     x=id%10;
//     y=(int)id/10;
//     y=y%10;
//     z=(int)id/100;

// }



// int Matrix::getCubes(int x, int y, int z){
//     return this->cubes[x][y][z];
// }
// Matrix::Matrix(int x_dim, int y_dim, int z_dim)
// {
//     this->x=x_dim;
//     this->y=y_dim;
//     this->z=z_dim;
//     // this->cubes[10][10][10];


//     for (int i = 0; i < x_dim; i++){
//         for (int j = 0; j < y_dim; i++){
//             for (int k = 0; k < z_dim; i++){
//                 cubes[i][j][k]= new Cube(i,j,k,false);
//             }
//         }
//     }
    
// }
