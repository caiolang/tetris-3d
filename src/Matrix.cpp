#include "Matrix.h"

Matrix::Matrix()
{
    // std::cout << "GOT INTO CONSTRUCTOR\n";

    /* Initializing the Matrix Cubes */
    for (int i = 0; i < 2200; i++)
    {
        m_cubes[i]= Cube(idToX(i), idToY(i), idToZ(i), false);
    }

    m_pieces.push_back( new O_piece());

}

void Matrix::rotatePieceX(int piece_id, int new_pos[]){
    Piece* piece = m_pieces[piece_id];

    // ERRO AO EXECUTAR A PROXIMA LINHA! COMO PROSSEGUIR? REESTRUTURAR O METODO DE ROTACAO?
    // piece->rotate_x(new_pos);

    std::cout << piece_id << " : " << m_pieces[piece_id];
    // m_pieces[piece_id]->rotate_x(new_pos);

}


void Matrix::initPiece(int piece_id){

    if( isSafe(m_pieces.at(piece_id)->getCubes()) ){
            std::cout << "\nIS SAFE\n";
            int color = m_pieces.at(piece_id)->getColor();
            setAsPiece(m_pieces.at(piece_id)->getCubes(),color);
        } else {
            std::cout << "\nNOT SAFE TO INITIALIZE PIECE\n";
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

    y=(int)id/100;
    return y;
}

int Matrix::idToZ(int id){
    int z;

    z=(int)id/10;
    z=z%10;
    return z;
}

Cube* Matrix::getCubes(){
    return m_cubes;
}

bool Matrix::isSafe(int* ids_vec){
    bool safe=true;
    int id=0;

    for (int i = 0; i < 4; i++)
    {
        id = ids_vec[i];
        if(this->m_cubes[id].isOccupied()){
            safe=false;
            std::cout << "\nCube of id " << id << " is not safe\n";
        }
    }
    
    return safe;
}


void Matrix::setAsPiece(int* ids_vec, int color){
    int id=0;

    for (int i = 0; i < 4; i++)
    {
        id = ids_vec[i];
        this->m_cubes[id].setColor(color);
        this->m_cubes[id].setOccupied(true);
    }
    
}

