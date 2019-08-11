#include <cursedtanks.h>

int Draw_First_Plan(sf::RenderWindow *window,
					sf::Sprite map_sprite,
					char **map,
					sf::Vector2f coord_object,
					short size)
{
		int x, y;
		for (int i = 0; i <= size; i += (size) / 2) {
			for (int j = 0; j <= size; j += (size) / 2) {
				x = (coord_object.x+i) / (SIZE_BASE_TILE / 2);
				y = (coord_object.y+j) / (SIZE_BASE_TILE / 2);
				switch(map[y*2][x*2]) {
					case TREE:
						map_sprite.setPosition(x*(SIZE_BASE_TILE/2), y*(SIZE_BASE_TILE/2));
						map_sprite.setTextureRect(sf::IntRect(264, 72, 8, 8));
                    	window->draw(map_sprite);
						break;
					case NONE:
					case BRICK:
					case ICE:
					case METAL:
					case WATER:
					case EMPTY:
					case BASE:
						break;
					default:
						return -1;
				}
			}
		}
		return 0;
}
