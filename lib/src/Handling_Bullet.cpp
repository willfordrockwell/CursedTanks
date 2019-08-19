#include <logic.h>

int Handling_Bullet(bullet_c *bullet,
                    float time)
{
    float tmp = (bullet->Get_Speed() * time);
    if (tmp >= 4.0) {
        tmp = 3.5;
    }
    if (bullet->Is_Active()) {
        switch(bullet->Get_Dir())
        {
        case UP:
            bullet->sprite.move(0, -(tmp));
            return 0;
        case DOWN:
            bullet->sprite.move(0, (tmp));
            return 0;
        case LEFT:
            bullet->sprite.move(-(tmp), 0);
            return 0;
        case RIGHT:
            bullet->sprite.move((tmp), 0);
            return 0;
        default:
            return -1;
        }
    }
    return 0;
}
