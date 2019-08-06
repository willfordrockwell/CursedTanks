#include <logic.h>
#define SMALL_SQUARE SMALL_SQUARE

int Validate_Bullet(char **map,            //double-ptr to map
                    struct bullet *bullet, //ptr to bullet
                    struct tank *tanks)    //all tanks
{
    int x_bullet = Get_Map_From_Pix(bullet->coord.x);
    int y_bullet = Get_Map_From_Pix(bullet->coord.y);

    switch (bullet->direct) //check tanks;
    {
    case UP:
        for (int i = 0; i < SMALL_SQUARE; i++)
            if (x_bullet == Get_Map_From_Pix(tanks->coord.x + SMALL_SQUARE * i)
                && y_bullet == Get_Map_From_Pix(tanks->coord.y + SMALL_SQUARE*3)) {
                bullet->coord.x = -16;
                bullet->coord.y = -16;
                tanks->health--;
                return 0;
            }
        break;
    case RIGHT:
        for (int i = 0; i < SMALL_SQUARE; i++)
            if (x_bullet == Get_Map_From_Pix(tanks->coord.x)
                && y_bullet == Get_Map_From_Pix(tanks->coord.y + SMALL_SQUARE * i)) {
                bullet->coord.x = -16;
                bullet->coord.y = -16;
                tanks->health--;
                return 0;
            }
        break;
    case LEFT:
        for (int i = 0; i < SMALL_SQUARE; i++)
            if (x_bullet == Get_Map_From_Pix(tanks->coord.x + SMALL_SQUARE*3)
                && y_bullet == Get_Map_From_Pix(tanks->coord.y + SMALL_SQUARE * i)) {
                bullet->coord.x = -16;
                bullet->coord.y = -16;
                tanks->health--;
                return 0;
            }
        break;
    case DOWN:
        for (int i = 0; i < SMALL_SQUARE; i++)
            if (x_bullet == Get_Map_From_Pix(tanks->coord.x + SMALL_SQUARE * i)
                && y_bullet == Get_Map_From_Pix(tanks->coord.y)) {
                bullet->coord.x = -16;
                bullet->coord.y = -16;
                tanks->health--;
                return 0;
            }
        break;
    }

    switch (map[x_bullet][y_bullet]) {
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
        return -1;
    }
}
