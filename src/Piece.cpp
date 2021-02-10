#include "Piece.h"
#include "Cube.h"

Piece::Piece(){
    m_stop= false;
    m_color= 100; // DEFAULT: White (TEMPORARY)
}

int* Piece::get_cubes(){
    return m_cube_position;
}

bool Piece::get_stop(){
    return m_stop;
}

int Piece::get_color(){
    return m_color;
}

void Piece::translate_x(int* new_pos, int dir){
    int step=1;
    if (dir<0){step=-1;}
    for(int i=0; i<4; i++){
        new_pos[i]=m_cube_position[i]+step;
    }
}

void Piece::translate_y(int* new_pos){
    for(int i=0; i<4; i++){
        new_pos[i]=m_cube_position[i]-100;
    }
}

void Piece::translate_z(int* new_pos,int dir){
    int step=1;
    if (dir<0){step=-1;}
    for(int i=0; i<4; i++){
        new_pos[i]=m_cube_position[i]+10*step;
    }
}
void Piece::rotate_x(int* new_pos){
    int coord[3][4];
    
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            if(i==0){
                coord[i][j]=m_cube_position[j]%10;
            }
            else if(i==1){
                coord[i][j]=(int) m_cube_position[j]/100;
            }
            else{
                coord[i][j]=(int) m_cube_position[j]/10;
                coord[i][j]=coord[i][j]%10;
            }
        }
    }

    new_pos[0]=m_cube_position[0];
    new_pos[1]=(coord[0][1])+(-coord[2][1]+coord[2][0]+coord[1][0])*100+(-coord[1][0]+coord[1][1]+coord[2][0])*10;
    new_pos[2]=(coord[0][2])+(-coord[2][2]+coord[2][0]+coord[1][0])*100+(-coord[1][0]+coord[1][2]+coord[2][0])*10;
    new_pos[3]=(coord[0][3])+(-coord[2][3]+coord[2][0]+coord[1][0])*100+(-coord[1][0]+coord[1][3]+coord[2][0])*10;
};

void Piece::rotate_z(int* new_pos){    
    int coord[3][4];
    
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            if(i==0){
                coord[i][j]=m_cube_position[j]%10;
            }
            else if(i==1){
                coord[i][j]=(int) m_cube_position[j]/100;
            }
            else{
                coord[i][j]=(int) m_cube_position[j]/10;
                coord[i][j]=coord[i][j]%10;
            }
        }
    }

    new_pos[0]=m_cube_position[0];
    new_pos[1]=(-coord[1][1]+coord[1][0]+coord[0][0])+(-coord[0][0]+coord[0][1]+coord[1][0])*100+(coord[2][1])*10;
    new_pos[2]=(-coord[1][2]+coord[1][0]+coord[0][0])+(-coord[0][0]+coord[0][2]+coord[1][0])*100+(coord[2][2])*10;
    new_pos[3]=(-coord[1][3]+coord[1][0]+coord[0][0])+(-coord[0][0]+coord[0][3]+coord[1][0])*100+(coord[2][3])*10;
}

void Piece::rotate_y(int* new_pos){
    int coord[3][4];
    
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            if(i==0){
                coord[i][j]=m_cube_position[j]%10;
            }
            else if(i==1){
                coord[i][j]=(int) m_cube_position[j]/100;
            }
            else{
                coord[i][j]=(int) m_cube_position[j]/10;
                coord[i][j]=coord[i][j]%10;
            }
        }
    }

    new_pos[0]=m_cube_position[0];
    new_pos[1]=(coord[2][1]-coord[2][0]+coord[0][0])+(coord[1][1])*100+(coord[0][0]-coord[0][1]+coord[2][0])*10;
    new_pos[2]=(coord[2][2]-coord[2][0]+coord[0][0])+(coord[1][2])*100+(coord[0][0]-coord[0][2]+coord[2][0])*10;
    new_pos[3]=(coord[2][3]-coord[2][0]+coord[0][0])+(coord[1][3])*100+(coord[0][0]-coord[0][3]+coord[2][0])*10;
}