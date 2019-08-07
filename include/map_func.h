#ifndef _MAP_FUNC_
#define _MAP_FUNC_

#include <SFML/Graphics.hpp>
#include <logic.h>

int Macro_To_Micro(sf::String *macro,
                   sf::String *micro);

int Draw_Map(sf::RenderWindow *window,
             sf::String *micro_map,
             sf::Sprite map_sprite);

#endif //_MAP_FUNC_
