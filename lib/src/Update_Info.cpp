#include <logic.h>

void Update_Info (struct info_to_player_s *server_info,  //ptr to server info
                  struct info_to_server_s *player_info)  //ptr to player info
{
    //update map
    for (int i = SIZE_MICRO_TILE; i < SIZE_MICRO_MAP_Y - SIZE_MICRO_TILE; i++) {
        for (int j = SIZE_MICRO_TILE; j < SIZE_MICRO_MAP_X - SIZE_MICRO_TILE; 
             j++) {
                if (server_info->map[i][j] > player_info->map[i][j])
                    server_info->map[i][j] = player_info->map[i][j];
        }
    }
    //update tank
    memcpy(&(server_info->tanks[(int)player_info->cli_num]),
           &(player_info->tank), SIZE_TANK);
    //update bullet
    memcpy(&(server_info->bullets[(int)player_info->cli_num]),
           &(player_info->bullet), SIZE_BULLET);
    return;
}