#include "Matrix.h"

Matrix::Matrix()
{

    /* Initializing the Matrix Cubes */
    for (int i = 0; i < 2200; i++)
    {
        m_cubes[i]= Cube(idToX(i), idToY(i), idToZ(i), false);
    }

    m_pieces.push_back( new O_piece());

    // m_curr_piece=m_pieces.at(0);

    // m_curr_piece=new O_piece();
    m_curr_piece=new I_piece();

}


void Matrix::rotatePieceX(){
    int* buffer;
    int oldCubes[4], newCubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    std::cout << "oldCubes: ";
    for(int i=0;i<4;i++){
        oldCubes[i]=buffer[i];
        std::cout << oldCubes[i] << ", ";
    }
    std::cout << "\n";

    this->m_curr_piece->rotateX();

    std::cout << "newCubes: ";
    for(int i=0;i<4;i++){
        newCubes[i]=buffer[i];
        std::cout << newCubes[i] << ", ";
    }
    std::cout << "\n";

    if(this->isSafeToMove(newCubes[0],newCubes[1],newCubes[2],newCubes[3],oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3])){
        this->setAsEmpty(oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3]);
        this->setAsPiece(newCubes[0],newCubes[1],newCubes[2],newCubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3]);
    }    
}

void Matrix::rotatePieceY(){
    int* buffer;
    int oldCubes[4], newCubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    std::cout << "oldCubes: ";
    for(int i=0;i<4;i++){
        oldCubes[i]=buffer[i];
        std::cout << oldCubes[i] << ", ";
    }
    std::cout << "\n";

    this->m_curr_piece->rotateY();

    std::cout << "newCubes: ";
    for(int i=0;i<4;i++){
        newCubes[i]=buffer[i];
        std::cout << newCubes[i] << ", ";
    }
    std::cout << "\n";

    if(this->isSafeToMove(newCubes[0],newCubes[1],newCubes[2],newCubes[3],oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3])){
        this->setAsEmpty(oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3]);
        this->setAsPiece(newCubes[0],newCubes[1],newCubes[2],newCubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3]);
    }    
}

void Matrix::rotatePieceZ(){
    int* buffer;
    int oldCubes[4], newCubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    std::cout << "oldCubes: ";
    for(int i=0;i<4;i++){
        oldCubes[i]=buffer[i];
        std::cout << oldCubes[i] << ", ";
    }
    std::cout << "\n";

    this->m_curr_piece->rotateZ();

    std::cout << "newCubes: ";
    for(int i=0;i<4;i++){
        newCubes[i]=buffer[i];
        std::cout << newCubes[i] << ", ";
    }
    std::cout << "\n";

    if(this->isSafeToMove(newCubes[0],newCubes[1],newCubes[2],newCubes[3],oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3])){
        this->setAsEmpty(oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3]);
        this->setAsPiece(newCubes[0],newCubes[1],newCubes[2],newCubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(oldCubes[0],oldCubes[1],oldCubes[2],oldCubes[3]);
    }    
}


void Matrix::initPiece(int piece_id){
    int* cubes = m_pieces.at(piece_id)->getCubes();


    if( isSafe(m_pieces.at(piece_id)->getCubes()) ){
            std::cout << "\nIS SAFE\n";
            int color = m_pieces.at(piece_id)->getColor();
            setAsPiece(cubes[0],cubes[1],cubes[2],cubes[3],color);
        } else {
            std::cout << "\nNOT SAFE TO INITIALIZE PIECE\n";
        }
}

void Matrix::initCurrPiece(){

    int* cubes = m_curr_piece->getCubes();

    if( isSafe(m_curr_piece->getCubes()) ){
            std::cout << "\nIS SAFE\n";
            int color = m_curr_piece->getColor();
            // setAsPiece(m_curr_piece->getCubes(),color);
            setAsPiece(cubes[0],cubes[1],cubes[2],cubes[3],color);
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

// TODO Checar limites do jogo
bool Matrix::isSafeToMove(int a0,int a1,int a2,int a3,int b0,int b1,int b2,int b3){
    bool safe=true;
    int id=0;
    int a[4]={a0,a1,a2,a3};
    int b[4]={b0,b1,b2,b3};

    for (int i = 0; i < 4; i++)
    {

        if(this->m_cubes[a[i]].isOccupied()){
            if(b[0]!=a[i] && b[1]!=a[i] && b[1]!=a[i] && b[3]!=a[i]){
                safe=false;
                std::cout << "\nCube of id " << a[i] << " is not safe\n";
            }

            
        }
    }
    
    return safe;
}


void Matrix::setAsPiece(int id0, int id1, int id2, int id3, int color){

    this->m_cubes[id0].setColor(color);
    this->m_cubes[id0].setOccupied(true);
    this->m_cubes[id1].setColor(color);
    this->m_cubes[id1].setOccupied(true);
    this->m_cubes[id2].setColor(color);
    this->m_cubes[id2].setOccupied(true);
    this->m_cubes[id3].setColor(color);
    this->m_cubes[id3].setOccupied(true);
    
}

void Matrix::setAsEmpty(int id0, int id1, int id2, int id3){
    int color=111;

    this->m_cubes[id0].setColor(color);
    this->m_cubes[id0].setOccupied(false);
    this->m_cubes[id1].setColor(color);
    this->m_cubes[id1].setOccupied(false);
    this->m_cubes[id2].setColor(color);
    this->m_cubes[id2].setOccupied(false);
    this->m_cubes[id3].setColor(color);
    this->m_cubes[id3].setOccupied(false);
    
}

