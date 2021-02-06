#include <iostream>

class Cube{
    private:
        int x, y, z;
        bool occupied;
    public:
        Cube(int pos_x, int pos_y, int pos_z, bool occ=false){   //Constructor with parameters
            x= pos_x;
            y= pos_y;
            z= pos_z;
            occupied= occ;
        }
        // Acess methods
        int get_x() {return x;}
        int get_y() {return y;}
        int get_z() {return z;}
        bool is_occupied() {return occupied;}
};