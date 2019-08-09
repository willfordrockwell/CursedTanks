#include <SFML/Graphics.hpp>
#include <map.h>
#include <cursedtanks.h>
#include <iostream>
#include <malloc.h>
using namespace sf;

int main()
{
	float time;
	Clock clock;
// Initial window
    RenderWindow window(VideoMode(704, 704), "CursedTanks");
    View view(FloatRect(0,0,352,352));
    window.setView(view);

// Initial map sprite
    char **micro_tile;
	micro_tile =(char** ) malloc(sizeof(char*) * SIZE_MICRO_MAP_Y);
	for (int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
		micro_tile[i] = (char* ) malloc(sizeof(char) * SIZE_MICRO_MAP_X);
	}
    Texture map_texture;
    Sprite map_sprite;
    map_texture.loadFromFile("textures/texture_map.png");
    map_sprite.setTexture(map_texture);
    map_sprite.setTextureRect(sf::IntRect(336, 0, 4, 4));

// Initial world object's sprites
    Color color(255,255,255);
    tank_c tank("textures/texture_map.png", 20 * 16, 17 * 16, 3, LEFT);
	tank.Set_Speed(0.025);
    bullet_c bullet("textures/texture_map.png", 19 * 16, 17 * 16, LEFT);
    if (Macro_To_Micro(macro_tile, micro_tile))
        std::cout << "Macro_map can't be read";

// Game cycle
    while (window.isOpen()) {
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
		Read_Keyboard(&tank, time);
        window.clear();
        Draw_Map(&window, micro_tile, map_sprite);
        window.draw(tank.sprite);
        window.draw(bullet.sprite);
        window.display();
    }

// Free memory
	for (int i =0; i < SIZE_MICRO_MAP_Y; i++) {
		free(micro_tile[i]);
	}
	free(micro_tile);

    return 0;
}
