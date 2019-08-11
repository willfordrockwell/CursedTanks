#include <network.h>

int Init_Socket(int *sock,                  //ptr to socket
                struct sockaddr_in *addr,   //ptr to addr
                socklen_t *size)            //ptr to addr size
{
    if ((*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("create socket");
        return -1;
    }

    while (bind(*sock, (struct sockaddr *)addr, *size) == -1) {
        switch (errno)
        {
        case EADDRINUSE:
        case EACCES:
            addr->sin_port = htons(htons(addr->sin_port) + 1);
            break;
        default:
            perror("bind");
            return -1;
        }
    }

    return 0;
}