#include <network.h>

void Send(int sock,                         //socket
          struct sockaddr_in *addr,         //data for connect
          socklen_t *size,                  //counted size
          char **map,                       //double-ptr to map
          struct bullet *bullets,           //ptr to bullets
          struct tank *tanks)               //ptr to tanks
{
    int size_map = sizeof(char) * MAP_SIDE * MAP_SIDE;
    int size_bullets = sizeof(struct bullet) * NUM_CLIENTS;
    int size_tanks = sizeof(struct tank) * NUM_CLIENTS;
    int size_buff = size_map + size_bullets + size_tanks;

    char buff[size_buff];

    memcpy(buff, map, size_map);
    memcpy(buff + size_map, bullets, size_bullets);
    memcpy(buff + size_map + size_bullets, tanks, size_tanks);

    sendto(sock, buff, size_buff, MSG_CONFIRM, (struct sockaddr*)addr,
           sizeof(addr));
}
