#include <logic.h>

int Validate_Bullet(char **map,         //double-ptr to map
                    bullet_c *bullets,  //ptr to bullet
                    tank_c *tanks,      //ptr to tanks
                    char number)        //number of clients
{
    sf::Vector2i coord;
    for (int i = 0; i < NUM_CLIENTS; i++) {
        if (bullets[i].Is_Active()) {
            for (int j = 0; j < SIZE_TILE; j += SIZE_TILE - 1) {
                switch (bullets[i].Get_Dir())
                {
                case UP:
                    coord = bullets[i].Get_Map_Position(j, 0);
                    break;
                case DOWN:
                    coord = bullets[i].Get_Map_Position(j, SIZE_TILE);
                    break;
                case LEFT:
                    coord = bullets[i].Get_Map_Position(0, j);
                    break;
                case RIGHT:
                    coord = bullets[i].Get_Map_Position(SIZE_TILE, j);
                    break;
                default:
                    return -1;
                }
                switch(map[coord.y][coord.x])
                {
                case EMPTY:
                case ICE:
                case WATER:
                case TREE:
                    break;
                case BASE:
                    if (i == number) {
                        for (int j = (coord.y / SIZE_TILE) * SIZE_TILE; j < ((coord.y / SIZE_TILE) * SIZE_TILE + SIZE_TILE); j++) {
                            for (int k = (coord.x / SIZE_TILE) * SIZE_TILE; k < ((coord.x / SIZE_TILE) * SIZE_TILE + SIZE_TILE); k++) {
                                map[j][k] = ICE;
                            }
                        }
                    }
                    bullets[i].sprite.setPosition(0, 0);
                    bullets[i].Set_Active(0);
                    break;
                case BRICK:
                    if (i == number) {
                        switch (bullets[i].Get_Dir())
                        {
                        case UP:
                        case DOWN:
                            if (map[coord.y][coord.x - 1] == BRICK)
                                map[coord.y][coord.x - 1] = EMPTY;
                            if (map[coord.y][coord.x + 1] == BRICK)
                                map[coord.y][coord.x + 1] = EMPTY;
                            if (map[coord.y][coord.x + 2] == BRICK)
                                map[coord.y][coord.x + 2] = EMPTY;
                            map[coord.y][coord.x] = EMPTY;
                            break;
                        case LEFT:
                        case RIGHT:
                            if (map[coord.y - 1][coord.x] == BRICK)
                                map[coord.y - 1][coord.x] = EMPTY;
                            if (map[coord.y + 1][coord.x] == BRICK)
                                map[coord.y + 1][coord.x] = EMPTY;
                            if (map[coord.y + 2][coord.x] == BRICK)
                                map[coord.y + 2][coord.x] = EMPTY;
                            map[coord.y][coord.x] = EMPTY;
                            break;
                        default:
                            return -1;
                        }
                    }
                    bullets[i].sprite.setPosition(0, 0);
                    bullets[i].Set_Active(0);
                    break;
                case METAL:
                case NONE:
                    bullets[i].sprite.setPosition(0, 0);
                    bullets[i].Set_Active(0);
                    break;
                default:
                    return -1;
                }
            }
        }
    }
    return 0;
}
