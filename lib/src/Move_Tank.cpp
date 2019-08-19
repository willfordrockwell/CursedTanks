#include <logic.h>

void Move_Tank(tank_c *tank,
               enum moving_e move,
               float time)
{
    switch (move)
    {
    case UP_BUTT:
        if (tank->Get_Dir() != UP) {
            tank->sprite.setPosition(((int)(tank->sprite.getPosition().x + 2) / 4) * 4,
                                     tank->sprite.getPosition().y);
            tank->Set_Dir(UP);
        }
        tank->sprite.move(0, -1 * tank->Get_Speed() * time);
        break;
    case DOWN_BUTT:
        if (tank->Get_Dir() != DOWN) {
            tank->sprite.setPosition(((int)(tank->sprite.getPosition().x + 2) / 4) * 4,
                                     tank->sprite.getPosition().y);
            tank->Set_Dir(DOWN);
        }
        tank->sprite.move(0, 1 * tank->Get_Speed() * time);
        break;
    case LEFT_BUTT:
        if (tank->Get_Dir() != LEFT) {
            tank->sprite.setPosition(tank->sprite.getPosition().x,
                                     (int)((tank->sprite.getPosition().y + 2) / 4) * 4);
            tank->Set_Dir(LEFT);
        }
        tank->sprite.move(-1 * tank->Get_Speed() * time, 0);
        break;
    case RIGHT_BUTT:
        if (tank->Get_Dir() != RIGHT) {
            tank->sprite.setPosition(tank->sprite.getPosition().x,
                                     (int)((tank->sprite.getPosition().y + 2) / 4) * 4);
            tank->Set_Dir(RIGHT);
        }
        tank->sprite.move(tank->Get_Speed() * time, 0);
        break;
    default:
        break;
    }
}