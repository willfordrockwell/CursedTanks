#ifndef __IO_H__
#define __IO_H__

#include <SFML/Graphics.hpp>
#include <logic.h>

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

void Read_Keyboard(sf::Event event,
                   bullet_c *bullet,
                   enum moving_e *move,
                   float time);

#endif // !__IO_H__
