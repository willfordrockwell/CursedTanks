#include <network.h>

int Recv_From_Server(int sock,                      //socket
                     struct sockaddr_in *addr,      //data for connect
                     socklen_t *size,               //counted size
                     struct info_to_player_s *info) //ptr to info
{

    int size_map = sizeof(char) * SIZE_MICRO_MAP_X * SIZE_MICRO_MAP_Y;
    int size_bullets = sizeof(struct bullet_s) * NUM_CLIENTS;
    int size_tanks = sizeof(struct tank_s) * NUM_CLIENTS;
    int size_buff = size_map + size_bullets + size_tanks;

    char buff[size_buff];
    if (recvfrom(sock, buff, size_buff, MSG_WAITALL, (struct sockaddr *)addr, size) < 1) {
        perror("Error recv start message");
        return -1;
    }
    memcpy(&(info->map), buff, size_map);
    memcpy(&(info->tanks), buff + size_map, size_tanks);
    memcpy(&(info->bullets), buff + size_map + size_tanks, size_bullets);
    return 0;
}
