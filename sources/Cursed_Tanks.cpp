#include <SFML/Graphics.hpp>
#include <map.h>
#include <cursedtanks.h>
#include <iostream>
using namespace sf;

int main()
{
// Initial window
    RenderWindow window(VideoMode(704, 704), "CursedTanks");
    View view(FloatRect(0,0,352,352));
    window.setView(view);

// Initial map sprite
    String micro_tile[SIZE_MICRO_MAP_X];
    for(int i = 0; i < SIZE_MICRO_MAP_X; i++) {
        micro_tile[i] = "0000000000000000000000000000000000\
						00000000000000000000000000000000000\
						00000000000000000000000000000000000\
						0000000000000000";
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
        std::cout << "Macro_map can't be read";

// Game cycle
    while (window.isOpen()) {
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
