#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "IO.h"

#define EMPTY   0
#define BRICK    1
#define TREE    2
#define METAL   3
#define WATER   4
#define ICE     5
#define BASE    6

#define MAP_SIDE 80

enum direct_e { UP, RIGHT, DOWN, LEFT };

struct coord_s {
    short x;
    short y;
};

struct tank_s {
    struct coord_s coord;
    enum direct_e direct;
    short health;
};

struct bullet_s {
    struct coord_s coord;
    enum direct_e direct;
};

int Get_Map_From_Pix (short x);

int Validate_Tank (char **map,          //double-ptr to map
                   struct tank *tank);  //ptr to tank

int Validate_Bullet (char **map,            //double-ptr to map
                     struct bullet *bullet, //ptr to bullet
                     struct tank *tanks);   //all tanks
#endif // !__LOGIC_H__
