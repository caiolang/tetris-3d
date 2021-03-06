#include "Matrix.h"

Matrix::Matrix()
{

    srand ((unsigned)time(NULL));
    int n;
    /* Initializing the Matrix Cubes */
    for (int i = 0; i < 2200; i++)
    {
        m_cubes[i]= Cube(idToX(i), idToY(i), idToZ(i), false);
        while( ( n = rand() ) > RAND_MAX - (RAND_MAX-6)%7 || n%7==m_list_pieces[i-1])
        { /* bad value retrieved so get next one */ }
        m_list_pieces[i]=n%7;
    }

    m_num_piece=0;

    m_curr_piece=new T_piece();
    m_curr_ghost=new T_piece();

    m_next_piece=new O_piece();
    m_next_ghost=new O_piece();
}

void Matrix::updateGhostPiece(){
    
    int* curr_cubes;
    int* ghost_cubes;
    int delta_y=100*getFreeDeltaY();
    int color = this->m_curr_piece->getColor();

    curr_cubes = this->m_curr_piece->getCubes();
    ghost_cubes = this->m_curr_ghost->getCubes();
    
    setAsNonGhost(ghost_cubes[0],ghost_cubes[1],ghost_cubes[2],ghost_cubes[3]);
    m_curr_ghost->setCubesPos(curr_cubes[0]-delta_y,curr_cubes[1]-delta_y,curr_cubes[2]-delta_y,curr_cubes[3]-delta_y);
    setAsGhost(curr_cubes[0]-delta_y,curr_cubes[1]-delta_y,curr_cubes[2]-delta_y,curr_cubes[3]-delta_y, color);
}


void Matrix::translatePieceX(int amount){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
    }

    this->m_curr_piece->translateX(amount);

    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
    }

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        // Updating cubes in Matrix
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    }    
}

void Matrix::translatePieceY(int amount){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
    }

    this->m_curr_piece->translateY(amount);

    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
    }
    
    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    }    
}

bool Matrix::autoTranslateCurrY(){
    int amount=-1;
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
    }

    this->m_curr_piece->translateY(amount);

    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
    }

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
        return true; // Returns true if movement was successful
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        // std::cout << "\nAuto translate of Current Piece wasn't safe\n";
        return false; // Returns false if movement was NOT successful
    }    
}

/* Verifies for eac cube of m_curr_piece the max it can go down in the
* y axis and returns the smaller between these distances
* @returns int - smaller free deltaY below the piece
*/
int Matrix::getFreeDeltaY(){
    int* buffer;
    int curr_cubes[4];

    buffer = this->m_curr_piece->getCubes();

    int curr_y[4];
    int curr_x[4];
    int curr_z[4];

   
    int dist_min=INT16_MAX;
    int delta_y=INT16_MAX;


    for(int i=0;i<4;i++){
        curr_cubes[i]=buffer[i];
        curr_x[i]=(int) curr_cubes[i]%10;
        curr_y[i]=(int) curr_cubes[i]/100;
        curr_z[i]=(int) curr_cubes[i]/10;
        curr_z[i]=curr_z[i]%10;
    }
   
    bool has_lower_neighbour=false;

    for(int i=0; i<4; i++){

        delta_y=INT16_MAX;
        has_lower_neighbour=false;

        for(int j=0; j<4; j++){
            if(i!=j && curr_x[i]==curr_x[j] && curr_z[i]==curr_z[j]){
                if(curr_y[i]>curr_y[j]){
                    has_lower_neighbour=true;
                } 
            }
        }


        if(!has_lower_neighbour){
            for(int y=curr_y[i]-1;y>=0; y--){
                if(m_cubes[curr_x[i]+curr_z[i]*10+y*100].isOccupied()){
                    if(curr_y[i]-y-1<delta_y){
                        delta_y=curr_y[i]-y-1;
                    }
                }
            }

        }
        
        if(curr_y[i]<delta_y){
            delta_y=curr_y[i];
        }

        if(delta_y<dist_min){
            dist_min=delta_y;
        }

    }
return dist_min;

}



void Matrix::translatePieceZ(int amount){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
    }

    this->m_curr_piece->translateZ(amount);

    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
    }

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    }    
}

void Matrix::rotatePieceX(){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
    }

    this->m_curr_piece->rotateX();

    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
    }

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    }    
}

void Matrix::rotatePieceY(){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
    }

    this->m_curr_piece->rotateY();

    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
    }

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    }    
}

void Matrix::rotatePieceZ(){
    int* buffer;
    int old_cubes[4], new_cubes[4];
    int color = this->m_curr_piece->getColor();

    buffer = this->m_curr_piece->getCubes();

    for(int i=0;i<4;i++){
        old_cubes[i]=buffer[i];
    }


    this->m_curr_piece->rotateZ();

    for(int i=0;i<4;i++){
        new_cubes[i]=buffer[i];
    }
  

    if(this->isSafeToMove(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3])){
        this->setAsEmpty(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
        this->setAsPiece(new_cubes[0],new_cubes[1],new_cubes[2],new_cubes[3],color);
    } else {
        this->m_curr_piece->setCubesPos(old_cubes[0],old_cubes[1],old_cubes[2],old_cubes[3]);
    }    
}

void Matrix::nextPiece(){
    int pieceType;
    this->m_curr_piece = this->m_next_piece;
    this->m_curr_ghost = this->m_next_ghost;

    
    pieceType = m_list_pieces[m_num_piece];
    m_num_piece+=1;
    if(m_num_piece>=2200){
        m_num_piece=0;
    }

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


bool Matrix::initCurrPiece(){

    int* cubes = m_curr_piece->getCubes();

    if( isFree(m_curr_piece->getCubes()) ){
            std::cout << "\nIT IS SAFE TO INIT PIECE\n";
            int color = m_curr_piece->getColor();
            setAsPiece(cubes[0],cubes[1],cubes[2],cubes[3],color);
            updateGhostPiece();
            return true;
    } else {
        std::cout << "\nNOT SAFE TO INIT PIECE\n";
        return false;
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
        return safe;
    }


    for (int i = 0; i < 4; i++)
    {
        
        // Checking if any of the new positions is occupied by OTHER pieces
        if(this->m_cubes[newPos[i]].isOccupied()){
            if(newPos[i]!=oldPos[0] && newPos[i]!=oldPos[1] && newPos[i]!=oldPos[2] && newPos[i]!=oldPos[3]){
                safe=false;
                return safe;
            }
        }

        // Checking if new position doesn't go out-of-bounds
        if(newPos[i]>2199 || newPos[i]<0){
            safe=false;
            return safe;
        }

        if( (idToX(newPos[i])==0 && idToX(oldPos[i])==9) || (idToX(newPos[i])==9 && idToX(oldPos[i])==0) ){
            safe=false;
            return safe;
        }

        if( (idToZ(newPos[i])==0 && idToZ(oldPos[i])==9) || (idToZ(newPos[i])==9 && idToZ(oldPos[i])==0) ){
            safe=false;
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

    this->m_cubes[id0].setGhost(false);
    this->m_cubes[id1].setGhost(false);
    this->m_cubes[id2].setGhost(false);
    this->m_cubes[id3].setGhost(false);
    
}

void Matrix::killGhost(){
    int* buffer;
    int ghost_cubes[4];

    buffer = this->m_curr_ghost->getCubes();

    for(int i=0;i<4;i++){
        ghost_cubes[i]=buffer[i];
    }

    this->setAsNonGhost(ghost_cubes[0],ghost_cubes[1],ghost_cubes[2],ghost_cubes[3]);
}

bool Matrix::checkGameOver(){

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(this->m_cubes[2100+i*10+j].isOccupied()){
                std::cout << "GAME OVER\n";
                return true;
            }
        }
    } 
    return false;

}

int Matrix::checkLine(){
    int completed_lines=0;
    for(int i=0; i<22; i++){
        for(int j=0; j<10; j++){
            int check_count1=0;
            int check_count2=0;
            for(int k=0; k<10; k++){
                if(this->m_cubes[i*100+10*j+k].isOccupied()){
                    check_count1++;
                }
                if(this->m_cubes[i*100+j+10*k].isOccupied()){
                    check_count2++;
                }
                if(check_count1==10){
                    clearLine(j,i, false);
                    j--;
                    completed_lines++;
                }
                if(check_count2==10){
                    clearLine(j,i, true);
                    j--;
                    completed_lines++;
                }
            }
        } 
    }
    return completed_lines;
}

void Matrix::clearLine(int start, int level, bool transverse = false){
    int color=111;
    int aux_color=111;
    if(transverse){
        for(int i=0; i<10 ; i++){
            this->m_cubes[100*level+start+10*i].setColor(color);
            this->m_cubes[100*level+start+10*i].setOccupied(false);
        }
        for(int k=level+1; k<22; k++){
            for(int i=0; i<10; i++){
                if(this->m_cubes[100*k+start+10*i].isOccupied()){
                    aux_color = this->m_cubes[100*k+start+10*i].getColor();
                    this->m_cubes[100*k+start+10*i].setOccupied(color);
                    this->m_cubes[100*k+start+10*i].setOccupied(false);
                    this->m_cubes[100*(k-1)+start+10*i].setOccupied(true);
                    this->m_cubes[100*(k-1)+start+10*i].setColor(aux_color);
                }
            }
        }
    }else{
        for(int i=0; i<10; i++){
            this->m_cubes[100*level+10*start+i].setColor(color);
            this->m_cubes[100*level+10*start+i].setOccupied(false);
            
        }
        for(int k=level+1; k<22; k++){
            for(int i=0; i<10; i++){
                if(this->m_cubes[100*k+10*start+i].isOccupied()){
                    aux_color = this->m_cubes[100*k+10*start+i].getColor();
                    this->m_cubes[100*k+10*start+i].setOccupied(color);
                    this->m_cubes[100*k+10*start+i].setOccupied(false);
                    this->m_cubes[100*(k-1)+10*start+i].setOccupied(true);
                    this->m_cubes[100*(k-1)+10*start+i].setColor(aux_color);
                }
            }
        }
    }
}
