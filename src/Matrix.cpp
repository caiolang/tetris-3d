#include "Matrix.h"

Matrix::Matrix()
{
    // std::cout << "GOT INTO CONSTRUCTOR\n";

    /* Initializing the Matrix Cubes */
    for (int i = 0; i < 2200; i++)
    {
        m_cubes[i]= Cube(id_to_x(i), id_to_y(i), id_to_z(i), false);
    }

    m_pieces.push_back( new O_piece());

}

void Matrix::rotate_piece_x(int piece_id, int new_pos[]){
    Piece* piece = m_pieces[piece_id];

    // ERRO AO EXECUTAR A PROXIMA LINHA! COMO PROSSEGUIR? REESTRUTURAR O METODO DE ROTACAO?
    // piece->rotate_x(new_pos);

    std::cout << piece_id << " : " << m_pieces[piece_id];
    // m_pieces[piece_id]->rotate_x(new_pos);

}


void Matrix::initialize_piece(int piece_id){

    if( is_safe(m_pieces.at(piece_id)->get_cubes()) ){
            std::cout << "\nIS SAFE\n";
            int color = m_pieces.at(piece_id)->get_color();
            set_as_piece(m_pieces.at(piece_id)->get_cubes(),color);
        } else {
            std::cout << "\nNOT SAFE TO INITIALIZE PIECE\n";
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

bool Matrix::is_safe(int* ids_vec){
    bool safe=true;
    int id=0;

    for (int i = 0; i < 4; i++)
    {
        id = ids_vec[i];
        if(this->m_cubes[id].is_occupied()){
            safe=false;
            std::cout << "\nCube of id " << id << " is not safe\n";
        }
    }
    
    return safe;
}


void Matrix::set_as_piece(int* ids_vec, int color){
    int id=0;

    for (int i = 0; i < 4; i++)
    {
        id = ids_vec[i];
        this->m_cubes[id].set_color(color);
        this->m_cubes[id].set_occupied(true);
    }
    
}

