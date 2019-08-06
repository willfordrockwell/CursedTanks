#include <network.h>

int Connect_To_Server(int *sock,              //ptr to socket
                      struct sockaddr_in *addr,//filled struct
                      socklen_t *size)         //counted size
{
    char buff[255];

    if ((*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("open socket to server");
        return -1;
    }

    sendto(*sock, buff, 255, MSG_CONFIRM, (struct sockaddr*)addr,
           *size);
    recvfrom(*sock, buff, 255, MSG_WAITALL, (struct sockaddr*)addr,
             size);
    return 0;
}
