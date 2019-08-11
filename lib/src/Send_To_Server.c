#include <network.h>

int Send_To_Server(int sock,                         //socket
                   struct sockaddr_in *addr,         //data about recv
                   socklen_t *size,                  //counted size
                   struct info_to_server_s *info)    //ptr to info
{
    const int size_buff = SIZE_MAP + SIZE_BULLET + SIZE_TANK + SIZE_CLI_NUM;

    char buff[size_buff];

    memcpy(buff, &(info->map), SIZE_MAP);
    memcpy(buff + SIZE_MAP, &(info->tank), SIZE_TANK);
    memcpy(buff + SIZE_MAP + SIZE_TANK, &(info->bullet), SIZE_BULLET);
    memcpy(buff + SIZE_MAP + SIZE_TANK + SIZE_BULLET, &(info->cli_num),
           SIZE_CLI_NUM);

    if (sendto(sock, buff, size_buff, MSG_CONFIRM, (struct sockaddr *)addr,
               *size) < 1) {
                    perror("Error send message to server");
                    return -1;
    }
    return 0;
}