#include <logic.h>

int Validate_Bullet (char **map,            //double-ptr to map
                     struct bullet *bullet, //ptr to bullet
                     struct tank *tanks     //all tanks
)
{
    int x_bullet = Get_Map_From_Pix(bullet->coord.x);
    int y_bullet = Get_Map_From_Pix(bullet->coord.y);

    //if material non-blocking as empty, tree, ice, continue fly
    if (map[x_bullet][y_bullet] == EMPTY)
        return 0;
    if (map[x_bullet][y_bullet] == TREE)
        return 0;
    if (map[x_bullet][y_bullet] == ICE)
        return 0;
    //remove after writing func
    return 0;
    //if material blocking as metal, "kill" bullet (set coord -1 -1)
    //if material destructable as rock, set EMPTY
    //check tanks, does one of them should be killed?
}
