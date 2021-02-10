#include "Piece.h"
#include "Cube.h"
#include "O_piece.h"

O_piece::O_piece()
{
    m_color=110; // Yellow
    m_cube_position[0]=2044;
    m_cube_position[1]=m_cube_position[0]+100;
    m_cube_position[3]=m_cube_position[0]+1;
    m_cube_position[2]=m_cube_position[1]+1;
    // std::cout << "Creating O_piece\n";
}

// void O_piece::rotate_x(int* new_pos){
//     int coord[3][4];
    
//     for(int i=0; i<3; i++){
//         for(int j=0; j<4; j++){
//             if(i==0){
//                 coord[i][j]=m_cube_position[j]%10;
//             }
//             else if(i==1){
//                 coord[i][j]=(int) m_cube_position[j]/100;
//             }
//             else{
//                 coord[i][j]=(int) m_cube_position[j]/10;
//                 coord[i][j]=coord[i][j]%10;
//             }
//         }
//     }

//     new_pos[0]=m_cube_position[0];
//     new_pos[1]=(coord[0][1])+(-coord[2][1]+coord[2][0]+coord[1][0])*100+(-coord[1][0]+coord[1][1]+coord[2][0])*10;
//     new_pos[2]=(coord[0][2])+(-coord[2][2]+coord[2][0]+coord[1][0])*100+(-coord[1][0]+coord[1][2]+coord[2][0])*10;
//     new_pos[3]=(coord[0][3])+(-coord[2][3]+coord[2][0]+coord[1][0])*100+(-coord[1][0]+coord[1][3]+coord[2][0])*10;
// };

// void O_piece::rotate_z(int* new_pos){    
//     int coord[3][4];
    
//     for(int i=0; i<3; i++){
//         for(int j=0; j<4; j++){
//             if(i==0){
//                 coord[i][j]=m_cube_position[j]%10;
//             }
//             else if(i==1){
//                 coord[i][j]=(int) m_cube_position[j]/100;
//             }
//             else{
//                 coord[i][j]=(int) m_cube_position[j]/10;
//                 coord[i][j]=coord[i][j]%10;
//             }
//         }
//     }

//     new_pos[0]=m_cube_position[0];
//     new_pos[1]=(-coord[1][1]+coord[1][0]+coord[0][0])+(-coord[0][0]+coord[0][1]+coord[1][0])*100+(coord[2][1])*10;
//     new_pos[2]=(-coord[1][2]+coord[1][0]+coord[0][0])+(-coord[0][0]+coord[0][2]+coord[1][0])*100+(coord[2][2])*10;
//     new_pos[3]=(-coord[1][3]+coord[1][0]+coord[0][0])+(-coord[0][0]+coord[0][3]+coord[1][0])*100+(coord[2][3])*10;
// }

// void O_piece::rotate_y(int* new_pos){
//     int coord[3][4];
    
//     for(int i=0; i<3; i++){
//         for(int j=0; j<4; j++){
//             if(i==0){
//                 coord[i][j]=m_cube_position[j]%10;
//             }
//             else if(i==1){
//                 coord[i][j]=(int) m_cube_position[j]/100;
//             }
//             else{
//                 coord[i][j]=(int) m_cube_position[j]/10;
//                 coord[i][j]=coord[i][j]%10;
//             }
//         }
//     }

//     new_pos[0]=m_cube_position[0];
//     new_pos[1]=(coord[2][1]-coord[2][0]+coord[0][0])+(coord[1][1])*100+(coord[0][0]-coord[0][1]+coord[2][0])*10;
//     new_pos[2]=(coord[2][2]-coord[2][0]+coord[0][0])+(coord[1][2])*100+(coord[0][0]-coord[0][2]+coord[2][0])*10;
//     new_pos[3]=(coord[2][3]-coord[2][0]+coord[0][0])+(coord[1][3])*100+(coord[0][0]-coord[0][3]+coord[2][0])*10;
// }