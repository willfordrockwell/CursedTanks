#ifndef _CURSED_TANKS_
#define _CURSED_TANKS_

#define SIZE_TILE 4

#define EMPTY   0
#define ROCK    1
#define TREE    2
#define METAL   3
#define WATER   4
#define ICE     5
#define BASE    6

#define MAP_SIDE 80

enum direct { UP, RIGHT, DOWN, LEFT };

struct coord {
    short x;
    short y;
};

struct tank {
    struct coord coord;
    enum direct direct;
    short health;
};

struct bullet {
    struct coord coord;
    enum direct direct;
};

int Get_Map_From_Pix (short x);

int Validate_Tank (char **map,          //double-ptr to map
                   struct tank *tank);  //ptr to tank

int Validate_Bullet (char **map,            //double-ptr to map
                     struct bullet *bullet, //ptr to bullet
                     struct tank *tanks);   //all tanks

#endif //_CURSED_TANKS_
