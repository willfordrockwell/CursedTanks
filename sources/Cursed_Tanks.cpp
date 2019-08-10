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
	Image map_image;
    Texture map_texture;
    Sprite map_sprite;
	map_image.loadFromFile("textures/texture_map.png");
	map_image.createMaskFromColor(Color(0,0,0,255), 0);
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);
    map_sprite.setTextureRect(sf::IntRect(336, 0, 4, 4));

// Initial world object's sprites
    Color color(255,255,255);
	tank_c tanks[4];
    tanks[0].Init("textures/texture_map.png", 20 * 16, 17 * 16, 3, LEFT);
//    tanks[1].Init("textures/texture_map.png", 20 * 16, 17 * 16, 2, LEFT);
	tanks[0].Set_Speed(0.020);

	bullet_c bullets[4];
    if (Macro_To_Micro(macro_tile, micro_tile))
        std::cout << "Macro_map can't be read";

// Game cycle
    while (window.isOpen()) {
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed){
                window.close();
			}
			if (event.type == Event::KeyPressed){
				if (event.key.code == Keyboard::Space) {
					if (!bullets[0].Is_Active())
					{
						Spawn_Bullet(event, tanks[0], &bullets[0]);
						bullets[0].Set_Speed(0.075);
					}
				}
			}
        }
		Read_Keyboard(&tanks[0], time);
		Validate_Tank(micro_tile, &tanks[0]);
		Handling_Bullet(&bullets[0], time);
		Validate_Bullet(micro_tile, bullets, tanks, 4);
        window.clear();
        Draw_Map(&window, micro_tile, map_sprite);
		Draw_Objects(&window, tanks, bullets, 4);
		for(int i = 0; i < 4; i++) {
			Draw_First_Plan(&window, map_sprite, micro_tile, tanks[i].sprite.getPosition(), 16);
			Draw_First_Plan(&window, map_sprite, micro_tile, bullets[i].sprite.getPosition(), 4);
		}
        window.display();
    }

// Free memory
	for (int i =0; i < SIZE_MICRO_MAP_Y; i++) {
		free(micro_tile[i]);
	}
	free(micro_tile);

    return 0;
}
