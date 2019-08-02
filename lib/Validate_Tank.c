#include "../include/logic.h"

int Validate_Tank (char **map,          //double-ptr to map
                   struct tank *tank    //ptr to tank
)
{
    int x = Get_Map_From_Pix(tank->coord.x);
    int y = Get_Map_From_Pix(tank->coord.y);

    if (map[x][y] == EMPTY)
        return 0;
    if (map[x][y] == TREE)
        return 0;
    if (map[x][y] == ICE)
        return 0;
    switch (tank->direct)
    {
    case UP:
        tank->coord.y++;
        return 0;
    case DOWN:
        tank->coord.y--;
        return 0;
    case RIGHT:
        tank->coord.x--;
        return 0;
    case LEFT:
        tank->coord.x++;
        return 0;
    default:
        return -1;
    }
}
