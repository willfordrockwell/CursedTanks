#include <SFML/Graphics.hpp>

#include <cursedtanks.h>

int Draw_Map(sf::RenderWindow *window,
             char **micro_map,
             sf::Sprite map_sprite)
{
	for(int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
        for(int j = 0; j < SIZE_MICRO_MAP_X; j++) {
			map_sprite.setPosition(j * SIZE_TILE, i * SIZE_TILE);
            switch(micro_map[i][j])
            {
            case EMPTY:
                map_sprite.setTextureRect(sf::IntRect(336, 0, 4, 4));
                window->draw(map_sprite);
                break;
            case BRICK:
                if ((((j % 2) + (i % 2)) == 1) || (((j % 2) + (i % 2)) == 3))
                    map_sprite.setTextureRect(sf::IntRect(268, 64, 4, 4));
                else
                    map_sprite.setTextureRect(sf::IntRect(268, 68, 4, 4));
                window->draw(map_sprite);
                break;
            case TREE:
                if((j % 2 == 0) && (i % 2 == 0)) {
                    map_sprite.setTextureRect(sf::IntRect(264, 72, 8, 8));
                    window->draw(map_sprite);
                }
                break;
            case METAL:
                if((j % 2 == 0) && (i % 2 == 0)) {
                    map_sprite.setTextureRect(sf::IntRect(256, 72, 8, 8));
                    window->draw(map_sprite);
                }
                break;
            case WATER:
                if((j % 2 == 0) && (i % 2 == 0)) {
                    if (j % 4 > 1)
                        map_sprite.setTextureRect(sf::IntRect(264, 80, 8, 8));
                    else
                        map_sprite.setTextureRect(sf::IntRect(272, 80, 8, 8));
                    window->draw(map_sprite);
                }
                break;
            case ICE:
                if((j % 4 == 0) && (i % 4 == 0)) {
                    map_sprite.setTextureRect(sf::IntRect(288, 32, 16, 16));
                    window->draw(map_sprite);
                }
                break;
            case BASE:
                if((j % 4 == 0) && (i % 4 == 0)) {
                    map_sprite.setTextureRect(sf::IntRect(304, 32, 16, 16));
                    window->draw(map_sprite);
                }
                break;
            case NONE:
                if((j % 2 == 0) && (i % 2 == 0)) {
                    map_sprite.setTextureRect(sf::IntRect(368, 0, 8, 8));
                    window->draw(map_sprite);
                }
                break;
            default:
                return -1;
            }
        }
    }
    return 0;
}
