#include <logic.h>

int Spawn_Bullet(tank_c tank,
                 bullet_c *bullet)
{
    switch(tank.Get_Dir())
    {
    case UP:
        bullet->Init("textures/texture_map.png",
        tank.sprite.getPosition().x + SIZE_TILE + 1,
        tank.sprite.getPosition().y - SIZE_TILE + 4, UP);
        break;
    case DOWN:
        bullet->Init("textures/texture_map.png",
        tank.sprite.getPosition().x + SIZE_TILE + 1,
        tank.sprite.getPosition().y + SIZE_BASE_TILE - 4, DOWN);
        break;
    case LEFT:
        bullet->Init("textures/texture_map.png",
        tank.sprite.getPosition().x - SIZE_TILE + 4,
        tank.sprite.getPosition().y + SIZE_TILE + 2, LEFT);
        break;
    case RIGHT:
        bullet->Init("textures/texture_map.png",
        tank.sprite.getPosition().x + SIZE_BASE_TILE - 4,
        tank.sprite.getPosition().y + SIZE_TILE + 2, RIGHT);
    default:
        return -1;
    }
    bullet->Set_Speed(0.075);
    return 0;
}
