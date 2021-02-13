#include "Matrix.h"

Matrix::Matrix()
{
    /* Initializing the Matrix Cubes */
    for (int i = 0; i < 2200; i++)
    {
        m_cubes[i]= Cube(idToX(i), idToY(i), idToZ(i), false);
    }

    m_curr_piece=new T_piece();
    m_curr_ghost=new T_piece();

    m_next_piece=new O_piece();
    m_next_ghost=new O_piece();
}

void Matrix::updateGhostPiece(){
    
    // bool flag=true;
    // int* buffer;
    // int curr_cubes[4];
    // int ghost_cubes[4];
    // buffer = this->m_curr_piece->getCubes();

    // std::cout << "Updating Ghost Piece\n";
    // this->m_curr_ghost->setCubesPos(curr_cubes[0],curr_cubes[1],curr_cubes[2],curr_cubes[3]);

    // while(flag){
    //     flag=autoTranslateGhostY();
    // }


}


void Matrix::translatePieceX(int amount){
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

    this->m_curr_piece->translateX(amount);

    // std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        // std::cout << new_cubes[i] << ", ";
    }
    // std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        // Updating cubes in Matrix
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        // std::cout << "\nMovement wasn't safe\n";
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

bool Matrix::autoTranslateCurrY(){
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

    // std::cout << "new cubes: ";
    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
        // std::cout << new_cubes[i] << ", ";
    }
    // std::cout << "\n";

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
        return true; // Returns true if movement was successful
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        std::cout << "\nAuto translate of Current Piece wasn't safe\n";
        return false; // Returns false if movement was NOT successful
    }    
}

int Matrix::getFreeDeltaY(){
    // verificar para cada cubo de m_curr_piece o y max que pode descer
    // retorna o menor dentre eles

    // esse valor sera usado para deslocar todas as pecas da ghost em y

    int* buffer;
    int curr_cubes[4];

    buffer = this->m_curr_piece->getCubes();

    int curr_y[4];
    int curr_x[4];
    int curr_z[4];

   
    int dist_min=0;


    for(int i=0;i<4;i++){
        curr_cubes[i]=buffer[i];
        // std::cout << curr_cubes[i] << ", ";
        curr_x[i]=(int) curr_cubes[i]%10;
        curr_y[i]=(int) curr_cubes[i]/100;
        curr_z[i]=(int) curr_cubes[i]/10;
        curr_z[i]=curr_z[i]%10;
    }
    std::cout << "curr_x: " << curr_x[0] << ", "<< curr_x[1] << ", "<< curr_x[2] << ", "<< curr_x[3] << "\n";
    std::cout << "curr_y: " << curr_y[0] << ", "<< curr_y[1] << ", "<< curr_y[2] << ", "<< curr_y[3] << "\n";
    std::cout << "curr_z: " << curr_z[0] << ", "<< curr_z[1] << ", "<< curr_z[2] << ", "<< curr_z[3] << "\n";

    /* REVER AQUI! */
    // bool same=false;
    // for(int i=0; i<4; i++){

    //     same=false;

    //     for(int j=0; j<4; j++){å
    //         if(curr_x[i]==curr_x[j] && curr_z[i]==curr_z[j]){
    //             if(curr_y[i]>curr_y[j]){
    //                 same=true;
    //             }
    //         }
    //     }

    //     if(!same){
    //         for(int y=curr_y[i]-1;y>=0; y--){
    //             if(m_cubes[curr_x[i]+curr_z[i]*10+y*100].isOccupied()){
    //                 if(curr_y[i]-y<dist_min){
    //                     dist_min=curr_y[i]-y;
    //                 }
    //             }
    //         }
    //     }   

    // }

std::cout << "dist_min: " << dist_min << "\n";
return dist_min;

}

bool Matrix::autoTranslateGhostY(){
    // std::cout << "autoTranslateGhostY()\n";
    // int amount=-1;
    // int* buffer;
    // int old_cubes[4], new_cubes[4];

    // int color = m_curr_ghost->getColor();
    // buffer = m_curr_ghost->getCubes();

    // std::cout << "old ghost cubes: ";
    // for(int i=0;i<4;i++){
    //     old_cubes[i]=buffer[i];
    //     std::cout << old_cubes[i] << ", ";
    // }
    // std::cout << "\n";

    // m_curr_ghost->translateY(amount);

    // std::cout << "new ghost cubes: ";
    // for(int i=0;i<4;i++){
    //     new_cubes[i]=buffer[i];
    //     std::cout << new_cubes[i] << ", ";
    // }
    // std::cout << "\n";

    // // if(true){
    // if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
    //     this->setAsNonGhost(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    //     this->setAsGhost(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    //     return true; // Returns true if movement was successful
    // } else {
    //     m_curr_ghost->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    //     std::cout << "\nAuto translate of Ghost Piece wasn't safe\n";
    //     return false; // Returns false if movement was NOT successful
    // }    
    return true;
}

void Matrix::translatePieceZ(int amount){
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

    this->m_curr_piece->translateZ(amount);

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

void Matrix::nextPiece(){
    int pieceType;
    this->m_curr_piece = this->m_next_piece;
    this->m_curr_ghost = this->m_next_ghost;

    srand (time(NULL));

    pieceType = rand() % 700;
    pieceType/=100;

    switch (pieceType)
    {
    case 0:
        this->m_next_piece=new I_piece();
        this->m_next_ghost=new I_piece();
        break;
    case 1:
        this->m_next_piece=new J_piece();
        this->m_next_ghost=new J_piece();
        break;
    case 2:
        this->m_next_piece=new L_piece();
        this->m_next_ghost=new I_piece();
        break;
    case 3:
        this->m_next_piece=new O_piece();
        this->m_next_ghost=new O_piece();
        break;
    case 4:
        this->m_next_piece=new S_piece();
        this->m_next_ghost=new S_piece();
        break;
    case 5:
        this->m_next_piece=new T_piece();
        this->m_next_ghost=new T_piece();
        break;
    case 6:
        this->m_next_piece=new Z_piece();
        this->m_next_ghost=new Z_piece();
        break;
    default:
        this->m_next_piece=new T_piece();
        this->m_next_ghost=new T_piece();
        break;
    }

}

void Matrix::initCurrPiece(){

    int* cubes = m_curr_piece->getCubes();

    if( isFree(m_curr_piece->getCubes()) ){
            std::cout << "\nIT IS SAFE TO INIT PIECE\n";
            int color = m_curr_piece->getColor();
            setAsPiece(cubes[0],cubes[1],cubes[2],cubes[3],color);
            initGhostPiece();
        } else {
            std::cout << "\nNOT SAFE TO INIT PIECE\n";
        }
}

void Matrix::initGhostPiece(){

    int* cubes = m_curr_ghost->getCubes();
    // std::cout << "\nGhost piece in starting id: " << cubes[0] << "\n";

    int color = m_curr_ghost->getColor();
    setAsGhost(cubes[0],cubes[1],cubes[2],cubes[3],color);
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
        // std::cout << "\nNot safe to move\n";
        return safe;
    }


    for (int i = 0; i < 4; i++)
    {
        
        // Checking if any of the new positions is occupied by OTHER pieces
        if(this->m_cubes[newPos[i]].isOccupied()){
            if(newPos[i]!=oldPos[0] && newPos[i]!=oldPos[1] && newPos[i]!=oldPos[2] && newPos[i]!=oldPos[3]){
                safe=false;
                // std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
                return safe;
            }
        }

        // Checking if new position doesn't go out-of-bounds
        if(newPos[i]>2199 || newPos[i]<0){
            safe=false;
            // std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
            return safe;
        }

        if( (idToX(newPos[i])==0 && idToX(oldPos[i])==9) || (idToX(newPos[i])==9 && idToX(oldPos[i])==0) ){
            safe=false;
            // std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
            return safe;
        }

        if( (idToZ(newPos[i])==0 && idToZ(oldPos[i])==9) || (idToZ(newPos[i])==9 && idToZ(oldPos[i])==0) ){
            safe=false;
            // std::cout << "\nCube of id " << newPos[i] << " is not safe\n";
            return safe;
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

void Matrix::setAsGhost(int id0, int id1, int id2, int id3, int color){

    this->m_cubes[id0].setColor(color);
    this->m_cubes[id0].setGhost(true);
    this->m_cubes[id1].setColor(color);
    this->m_cubes[id1].setGhost(true);
    this->m_cubes[id2].setColor(color);
    this->m_cubes[id2].setGhost(true);
    this->m_cubes[id3].setColor(color);
    this->m_cubes[id3].setGhost(true);
    
}

void Matrix::setAsNonGhost(int id0, int id1, int id2, int id3){
    int color=111;

    this->m_cubes[id0].setColor(color);
    this->m_cubes[id0].setGhost(false);
    this->m_cubes[id1].setColor(color);
    this->m_cubes[id1].setGhost(false);
    this->m_cubes[id2].setColor(color);
    this->m_cubes[id2].setGhost(false);
    this->m_cubes[id3].setColor(color);
    this->m_cubes[id3].setGhost(false);
    
}

