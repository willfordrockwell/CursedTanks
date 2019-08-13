#include <logic.h>
#include <iostream>
int Validate_Tank (char **map,       //double-ptr to map
                   tank_c *tank)     //ptr to tank
{
    sf::Vector2i coord_map;

    switch(tank -> Get_Dir())
    {
        case UP: {
            for (int i = 0; i < SIZE_BASE_TILE; i += 1) {
                coord_map = tank -> Get_Map_Position(i, 0);
				switch (map[coord_map.y][coord_map.x]) {
                    case NONE:
                    case BASE:
                    case WATER:
                    case METAL:
                    case BRICK:
                        tank -> sprite.setPosition(tank -> sprite.getPosition().x, (coord_map.y+1)*SIZE_TILE);
					case EMPTY:
					case ICE:
					case TREE:
						break;
					default:
						return -1;
                }
			}
		return 0;
		}
        case DOWN: {
            for (int i = 0; i < SIZE_BASE_TILE; i += 1) {
                coord_map = tank -> Get_Map_Position(i, SIZE_BASE_TILE);
                switch (map[coord_map.y][coord_map.x]) {
                    case NONE:
                    case BASE:
                    case WATER:
                    case METAL:
                    case BRICK:
                        tank -> sprite.setPosition(tank -> sprite.getPosition().x, (coord_map.y-SIZE_TILE)*SIZE_TILE);
					case EMPTY:
					case ICE:
					case TREE:
						break;
                	default:
						return -1;
				}
			}
		return 0;
		}
        case RIGHT: {
            for (int i = 0; i < SIZE_BASE_TILE; i += 1) {
                coord_map = tank -> Get_Map_Position(SIZE_BASE_TILE, i);
                switch (map[coord_map.y][coord_map.x]) {
                    case NONE:
                    case BASE:
                    case WATER:
                    case METAL:
                    case BRICK:
                        tank -> sprite.setPosition((coord_map.x-SIZE_TILE)*SIZE_TILE, tank -> sprite.getPosition().y);
                        return 0;
					case EMPTY:
					case ICE:
					case TREE:
						break;
					default:
						return -1;
                }
			}
			return 0;
		}
        case LEFT: {
            for (int i = 0; i < SIZE_BASE_TILE; i += 1) {
                coord_map = tank -> Get_Map_Position(0, i);
                switch (map[coord_map.y][coord_map.x]) {
                    case NONE:
                    case BASE:
                    case WATER:
                    case METAL:
                    case BRICK:
                        tank -> sprite.setPosition((coord_map.x+1)*SIZE_TILE, tank -> sprite.getPosition().y);
                        return 0;
					case EMPTY:
					case ICE:
					case TREE:
						break;
					default:
						return -1;
                }
			}
			return 0;
		}
		default:
			return -1;
    }
}
