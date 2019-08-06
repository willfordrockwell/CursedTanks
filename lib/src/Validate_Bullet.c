#include "../include/logic.h"

int Validate_Bullet (char **map,            //double-ptr to map
                     struct bullet *bullet, //ptr to bullet
                     struct tank *tanks)    //all tanks
{
    int x_bullet = Get_Map_From_Pix(bullet->coord.x);
    int y_bullet = Get_Map_From_Pix(bullet->coord.y);

    //TODO: check tanks;

    switch(map[x_bullet][y_bullet])
    {
    case EMPTY:
    case WATER:
    case TREE:
    case ICE:
        return 0;
    case BRICK:
        map[x_bullet][y_bullet] = EMPTY;
    case METAL:
        bullet->coord.x = -16;
        bullet->coord.y = -16;
        return 0;
    default:
        return 1;
    }
}
