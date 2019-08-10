#include <cursedtanks.h>
#include <iostream>

int Validate_Bullet(char **map,
                    bullet_c *bullets,
                    tank_c *tanks,
					short num_arrays)
{
	sf::Vector2i coord;
	if (bullets[0].Is_Active())
		for(int i = 0; i < SIZE_TILE; i += SIZE_TILE-1) {
			switch(bullets[0].Get_Dir()){
				case UP:
					coord = bullets[0].Get_Map_Position(i, 0);
					break;
				case DOWN:
					coord = bullets[0].Get_Map_Position(i, SIZE_TILE);
					break;
				case LEFT:
					coord = bullets[0].Get_Map_Position(0, i);
					break;
				case RIGHT:
					coord = bullets[0].Get_Map_Position(SIZE_TILE, i);
					break;
				default:
					return -1;
			}
   	     	switch(map[coord.y][coord.x]) {
				case EMPTY:
				case ICE:
				case WATER:
				case TREE:
					break;
   	            case BASE:
					for(int i = (coord.y/SIZE_TILE) * SIZE_TILE; i < ((coord.y/SIZE_TILE) * SIZE_TILE + SIZE_TILE); i++) {
						for(int j = (coord.x/SIZE_TILE) * SIZE_TILE; j < ((coord.x/SIZE_TILE) * SIZE_TILE + SIZE_TILE); j++) {
							map[i][j] = ICE;
						}
					}
					bullets[0].sprite.setPosition(0, 0);
					bullets[0].Set_Active(0);
					break;
				case BRICK:
					switch(bullets[0].Get_Dir()) {
						case UP:
						case DOWN:
							if(map[coord.y][coord.x - 1] == BRICK) map[coord.y][coord.x - 1] = EMPTY;
							if(map[coord.y][coord.x + 1] == BRICK) map[coord.y][coord.x + 1] = EMPTY;
							if(map[coord.y][coord.x + 2] == BRICK) map[coord.y][coord.x + 2] = EMPTY;
							map[coord.y][coord.x] = EMPTY;
							break;
						case LEFT:
						case RIGHT:
							if(map[coord.y - 1][coord.x] == BRICK) map[coord.y - 1][coord.x] = EMPTY;
							if(map[coord.y + 1][coord.x] == BRICK) map[coord.y + 1][coord.x] = EMPTY;
							if(map[coord.y + 2][coord.x] == BRICK) map[coord.y + 2][coord.x] = EMPTY;
							map[coord.y][coord.x] = EMPTY;
						break;
						default:
							return -1;
					}
					bullets[0].sprite.setPosition(0, 0);
			    	bullets[0].Set_Active(0);
					break;
   	            case METAL:
				case NONE:
					bullets[0].sprite.setPosition(0, 0);
					bullets[0].Set_Active(0);
					break;
				default:
					return -1;
			}
	}
	return 0;
}
