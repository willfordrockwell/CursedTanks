#include <network.h>

void Recv(int socket,                       //socket
          struct sockaddr_in *addr,         //data for connect
          socklen_t *size,                  //data for connect
          char **map,                       //double-ptr to map
          struct bullet *bullets,           //ptr to bullets
          struct tank *tanks)               //ptr to tanks
{
    int size_map = sizeof(char) * MAP_SIDE * MAP_SIDE;
    int size_bullets = sizeof(struct bullet) * NUM_CLIENTS;
    int size_tanks = sizeof(struct tank) * NUM_CLIENTS;
    int size_buff = size_map + size_bullets + size_tanks;
  
    char buff[size_buff];
    recvfrom(socket, buff, size_buff, MSG_WAITALL,
             (struct sockaddr*)addr, size);

    memcpy(map, buff, size_map);
    memcpy(bullets, buff + size_map, size_bullets);
    memcpy(tanks, buff + size_map + size_bullets, size_tanks);
}
