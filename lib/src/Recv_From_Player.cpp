#include <network.h>

int Recv_From_Player(int sock,                       //socket
                     struct info_to_server_s *info)  //ptr to info
{
    const int size_buff = SIZE_MAP + SIZE_BULLET + SIZE_TANK + SIZE_CLI_NUM;

    char buff[size_buff];
    struct sockaddr_in addr;
    socklen_t size = sizeof(addr);

    if (recvfrom(sock, buff, size_buff, MSG_WAITALL, (struct sockaddr *)&addr,
        &size) < 1) {
            perror("Error recv message from player");
            return -1;
    }
    memcpy(&(info->map), buff, SIZE_MAP);
    memcpy(&(info->tank), buff + SIZE_MAP, SIZE_TANK);
    memcpy(&(info->bullet), buff + SIZE_MAP + SIZE_TANK, SIZE_BULLET);
    memcpy(&(info->cli_num), buff + SIZE_MAP + SIZE_TANK + SIZE_BULLET,
           SIZE_CLI_NUM);
    return 0;
}