#ifndef _MAP_FUNC_
#define _MAP_FUNC_

#include <SFML/Graphics.hpp>
#include <logic.h>

int Macro_To_Micro(sf::String *macro,
                   char **micro);

int Draw_Map(sf::RenderWindow *window,
             char **micro_map,
             sf::Sprite map_sprite);

int Draw_First_Plan(sf::RenderWindow *window,
					sf::Sprite map_sprite,
					char **map,
					sf::Vector2f coord_object);

#endif //_MAP_FUNC_
