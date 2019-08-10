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
					sf::Vector2f coord_object,
					short size);

int Draw_Objects(sf::RenderWindow *window,
				 tank_c *tanks,
				 bullet_c *bullets,
				 int objects_num);

int Spawn_Bullet(sf::Event event,
				 tank_c tank,
				 bullet_c *bullet);

#endif //_MAP_FUNC_
