#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "IO.h"

#define EMPTY   '0'
#define BRICK   '1'
#define TREE    '2'
#define METAL   '3'
#define WATER   '4'
#define ICE     '5'
#define BASE    '6'
#define NONE    '7'

#define MAP_SIDE 80

#define SIZE_MICRO_TILE 	4
#define SIZE_MICRO_MAP_X 	88
#define SIZE_MICRO_MAP_Y 	88
#define SIZE_MACRO_TILE 	16
#define SIZE_MACRO_MAP_X 	20
#define SIZE_MACRO_MAP_Y 	20


enum direct_e { UP, LEFT, DOWN, RIGHT };

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
                   struct tank_s *tank);  //ptr to tank

int Validate_Bullet (char **map,            //double-ptr to map
                     struct bullet_s *bullet, //ptr to bullet
                     struct tank_s *tanks);   //all tanks
#endif // !__LOGIC_H__
