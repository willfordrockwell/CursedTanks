#include <network.h>

int Send_To_Player(int sock,                         //socket
                   struct sockaddr_in addr,          //data about recv
                   socklen_t size,                   //counted size
                   struct info_to_player_s *info)    //ptr to info
{
    const int size_buff = SIZE_MAP + SIZE_TANKS + SIZE_BULLETS;

    char buff[size_buff];

    memcpy(buff, &(info->map), SIZE_MAP);
    memcpy(buff + SIZE_MAP, &(info->tanks), SIZE_TANKS);
    memcpy(buff + SIZE_MAP + SIZE_TANKS, &(info->bullets), SIZE_BULLETS);

    if (sendto(sock, buff, size_buff, MSG_CONFIRM, (struct sockaddr *)&addr,
               size) < 1) {
                perror("send message to player");
                return -1;
    }
    return 0;
}
