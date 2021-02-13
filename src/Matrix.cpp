#include "Matrix.h"

Matrix::Matrix()
{

    /* Initializing the Matrix Cubes */
    for (int i = 0; i < 2200; i++)
    {
        m_cubes[i]= Cube(idToX(i), idToY(i), idToZ(i), false);
    }

    // m_pieces.push_back( new O_piece());

    // m_curr_piece=m_pieces.at(0);
    // m_curr_piece=new O_piece();

    m_curr_piece=new T_piece();
    m_next_piece=new O_piece();
}

void Matrix::translatePieceX(int amount){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    std::cout << "old cubes: ";
    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
        std::cout << old_cubes[i] << ", ";
    }
    std::cout << "\n";

    this->m_curr_piece->translateX(amount);

    std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        std::cout << new_cubes[i] << ", ";
    }
    std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        // Updating cubes in Matrix
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        std::cout << "\nMovement wasn't safe\n";
    }    
}




void Matrix::translatePieceY(int amount){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    // std::cout << "old cubes: ";
    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
        // std::cout << old_cubes[i] << ", ";
    }
    // std::cout << "\n";

    this->m_curr_piece->translateY(amount);

    std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        std::cout << new_cubes[i] << ", ";
    }
    std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        std::cout << "\nMovement wasn't safe\n";
    }    
}

bool Matrix::autoTranslateY(){
    int amount=-1;
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    // std::cout << "old cubes: ";
    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
        // std::cout << old_cubes[i] << ", ";
    }
    // std::cout << "\n";

    this->m_curr_piece->translateY(amount);

    std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        std::cout << new_cubes[i] << ", ";
    }
    std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
        return true; // Returns true if movement was successful
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        std::cout << "\nMovement wasn't safe\n";
        return false; // Returns false if movement was NOT successful
    }    
}

void Matrix::translatePieceZ(int amount){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    std::cout << "old cubes: ";
    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
        std::cout << old_cubes[i] << ", ";
    }
    std::cout << "\n";

    this->m_curr_piece->translateZ(amount);

    std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        std::cout << new_cubes[i] << ", ";
    }
    std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        std::cout << "\nMovement wasn't safe\n";
    }    
}


void Matrix::rotatePieceX(){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    // std::cout << "old cubes: ";
    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
        // std::cout << old_cubes[i] << ", ";
    }
    // std::cout << "\n";

    this->m_curr_piece->rotateX();

    // std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        // std::cout << new_cubes[i] << ", ";
    }
    // std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        // std::cout << "\nMovement wasn't safe\n";
    }    
}

void Matrix::rotatePieceY(){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    // std::cout << "old cubes: ";
    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
        // std::cout << old_cubes[i] << ", ";
    }
    // std::cout << "\n";

    this->m_curr_piece->rotateY();

    // std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        // std::cout << new_cubes[i] << ", ";
    }
    // std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        // std::cout << "\nMovement wasn't safe\n";
    }    
}

void Matrix::rotatePieceZ(){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    // std::cout << "old cubes: ";
    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
        // std::cout << old_cubes[i] << ", ";
    }
    // std::cout << "\n";

    this->m_curr_piece->rotateZ();

    // std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        std::cout << new_cubes[i] << ", ";
    }
    // std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        std::cout << "\nMovement wasn't safe\n";
    }    
}


// void Matrix::initPiece(int piece_id){
//     int* cubes = m_pieces.at(piece_id)->getCubes();

//     if( isFree(m_pieces.at(piece_id)->getCubes()) ){
//             std::cout << "\nIS SAFE\n";
//             int color = m_pieces.at(piece_id)->getColor();
//             setAsPiece(cubes[0],cubes[1],cubes[2],cubes[3],color);
//         } else {
//             std::cout << "\nNOT SAFE TO INITIALIZE PIECE\n";
//         }
// }

void Matrix::nextPiece(){
    int pieceType;
    this->m_curr_piece = this->m_next_piece;
    srand (time(NULL));

    pieceType = rand() % 700;
    pieceType/=100;

    switch (pieceType)
    {
    case 0:
        this->m_next_piece=new I_piece();
        break;
    case 1:
        this->m_next_piece=new J_piece();
        break;
    case 2:
        this->m_next_piece=new L_piece();
        break;
    case 3:
        this->m_next_piece=new O_piece();
        break;
    case 4:
        this->m_next_piece=new S_piece();
        break;
    case 5:
        this->m_next_piece=new T_piece();
        break;
    case 6:
        this->m_next_piece=new Z_piece();
        break;
    default:
        this->m_next_piece=new T_piece();
        break;
    }

}

void Matrix::initCurrPiece(){

    int* cubes = m_curr_piece->getCubes();

    if( isFree(m_curr_piece->getCubes()) ){
            std::cout << "\nIS SAFE\n";
            int color = m_curr_piece->getColor();
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

bool Matrix::isFree(int* ids_vec){
    bool safe=true;
    int id=0;

    for (int i = 0; i < 4; i++)
    {
        id = ids_vec[i];
        if(this->m_cubes[id].isOccupied()){
            safe=false;
            std::cout << "\nCube of id " << id << " is not free\n";
        }
    }
    
    return safe;
}

bool Matrix::isSafeToMove(int new0,int new1,int new2,int new3,int old0,int old1,int old2,int old3){
    bool safe=true;
    int id=0;
    int newPos[4]={new0,new1,new2,new3};
    int oldPos[4]={old0,old1,old2,old3};
    int coord[3][4];
    
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            if(i==0){
                coord[i][j]=newPos[j]%10;
            }
            else if(i==1){
                coord[i][j]=(int) newPos[j]/100;
            }
            else{
                coord[i][j]=(int) newPos[j]/10;
                coord[i][j]=coord[i][j]%10;
            }
        }
    }
    int dist1 = std::abs(coord[0][1]-coord[0][0])+std::abs(coord[1][1]-coord[1][0])+std::abs(coord[2][1]-coord[2][0]);
    int dist2 = std::abs(coord[0][2]-coord[0][0])+std::abs(coord[1][2]-coord[1][0])+std::abs(coord[2][2]-coord[2][0]);
    int dist3 = std::abs(coord[0][3]-coord[0][0])+std::abs(coord[1][3]-coord[1][0])+std::abs(coord[2][3]-coord[2][0]);
    if(dist1>4 || dist2>4 || dist3>4){
        safe=false;
        std::cout << "\nNot safe\n";
        return safe;
    }


    for (int i = 0; i < 4; i++)
    {
        
        // Checking if any of the new positions is occupied by OTHER pieces
        if(this->m_cubes[newPos[i]].isOccupied()){
            if(newPos[i]!=oldPos[0] && newPos[i]!=oldPos[1] && newPos[i]!=oldPos[2] && newPos[i]!=oldPos[3]){
                safe=false;
                std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
                return safe;
            }
        }

        // Checking if new position doesn't go out-of-bounds
        if(newPos[i]>2199 || newPos[i]<0){
            safe=false;
            std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
            return safe;
        }

        if( (idToX(newPos[i])==0 && idToX(oldPos[i])==9) || (idToX(newPos[i])==9 && idToX(oldPos[i])==0) ){
            safe=false;
            std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
            return safe;
        }

        if( (idToZ(newPos[i])==0 && idToZ(oldPos[i])==9) || (idToZ(newPos[i])==9 && idToZ(oldPos[i])==0) ){
            safe=false;
            std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
            return safe;
        }

        // if( (idToZ(newPos[i])==0 && idToZ(oldPos[i])==9) || (idToZ(newPos[i])==9 && idToZ(oldPos[i])==0) ){
        //     safe=false;
        //     std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
        //     return safe;
        // }




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

