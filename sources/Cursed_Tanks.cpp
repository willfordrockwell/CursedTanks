#include <SFML/Graphics.hpp>
#include <map.h>
#include <cursedtanks.h>
#include <iostream>
using namespace sf;

int Draw_Map(RenderWindow *window,
             String *micro_map,
             Sprite map_sprite)
{
    for(int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
        std::cout<<"\n";
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

int main()
{
    // Initial window
    RenderWindow window(VideoMode(704, 704), "CursedTanks");
    View view(FloatRect(0,0,352,352));
    window.setView(view);

    // Initial map sprite
    String micro_tile[SIZE_MICRO_MAP_X];
    for(int i = 0; i < SIZE_MICRO_MAP_X; i++) {
        micro_tile[i] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    }
    Texture map_texture;
    Sprite map_sprite;
    map_texture.loadFromFile("textures/texture_map.png");
    map_sprite.setTexture(map_texture);
    map_sprite.setTextureRect(sf::IntRect(336, 0, 4, 4));

// Initial world object's sprites
    Color color(255,255,255);
    tank_c tank("textures/texture_map.png", 20 * 16, 17 * 16, 3, LEFT);
    bullet_c bullet("textures/texture_map.png", 19 * 16, 17 * 16, LEFT);
    if (Macro_To_Micro(macro_tile, micro_tile))
        std::cout <<"Macro_map can't be read";
// Game cycle
    while (window.isOpen()) {
        //fo
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        Draw_Map(&window, micro_tile, map_sprite);
        window.draw(tank.sprite);
        window.draw(bullet.sprite);
        window.display();
    }
    return 0;
}
