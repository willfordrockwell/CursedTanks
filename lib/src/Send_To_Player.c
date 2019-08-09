#include <network.h>

int Send_To_Player(int sock,                         //socket
                   struct sockaddr_in *addr,         //data for connect
                   socklen_t *size,                  //counted size
                   struct info_to_player_s *info)    //ptr to info
{

    int size_map = sizeof(char) * SIZE_MICRO_MAP_X * SIZE_MICRO_MAP_Y;
    int size_bullets = sizeof(struct bullet_s) * NUM_CLIENTS;
    int size_tanks = sizeof(struct tank_s) * NUM_CLIENTS;
    int size_buff = size_map + size_bullets + size_tanks;

    char buff[size_buff];

    memcpy(buff, &(info->map), size_map);
    memcpy(buff + size_map, &(info->tanks), size_tanks);
    memcpy(buff + size_map + size_tanks, &(info->bullets), size_bullets);

    if (sendto(sock, buff, size_buff, MSG_CONFIRM, (struct sockaddr *)addr, *size) < 1) {
        perror("Error send start message");
        return -1;
    }
    return 0;
}
