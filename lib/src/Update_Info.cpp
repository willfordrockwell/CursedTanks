#include <logic.h>

void Update_Info (struct info_to_player_s *server_info,  //ptr to server info
                  struct info_to_server_s *player_info)  //ptr to player info
{
    //update map
    for (int i = SIZE_MACRO_TILE; i < SIZE_MICRO_MAP_Y - SIZE_MACRO_TILE; i++) {
        for (int j = SIZE_MACRO_TILE; j < SIZE_MICRO_MAP_X - SIZE_MACRO_TILE; 
             j++) {
                if (server_info->map[i][j] > player_info->map[i][j])
                    server_info->map[i][j] = player_info->map[i][j];
        }
    }
    //update tank coord
    server_info->tanks[(int)(player_info->cli_num)].coord.x
    = player_info->tank.coord.x;
    server_info->tanks[(int)(player_info->cli_num)].coord.y
    = player_info->tank.coord.y;
    //update tank direct
    server_info->tanks[(int)(player_info->cli_num)].direct
    = player_info->tank.direct;
    //update tank health
    server_info->tanks[(int)(player_info->cli_num)].health
    = player_info->tank.health;
    //update bullet coord
    server_info->bullets[(int)(player_info->cli_num)].coord.x
    = player_info->bullet.coord.x;
    server_info->bullets[(int)(player_info->cli_num)].coord.y
    = player_info->bullet.coord.y;
    //update bullet direct
    server_info->bullets[(int)(player_info->cli_num)].direct
    = player_info->bullet.direct;
    return;
}