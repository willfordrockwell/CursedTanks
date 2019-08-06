
#include <network.h>

int Connect_To_Client(int sock,                //socket
                      struct sockaddr_in *addr,//filled struct
                      socklen_t *size)         //counted size
{
    char buff[255];

    recvfrom(sock, buff, 255, MSG_WAITALL, (struct sockaddr*)addr,
             size);
    sendto(sock, buff, 255, MSG_CONFIRM, (struct sockaddr*)addr,
           *size);
    return 0;
}


