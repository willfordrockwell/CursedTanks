#include <IO.h>

int Draw_Objects (sf::RenderWindow *window,
                  tank_c *tanks,
                  bullet_c *bullets,
                  int objects_num)
{
    for (int i = 0; i < objects_num; i++){
        if (bullets[i].Is_Active())
            window -> draw(bullets[i].sprite);

        if (tanks[i].Is_Active())
            window -> draw(tanks[i].sprite);
    }
    return 0;
}
