#include <network.h>

int Init_Server(int *sock,                  //ptr to socket
                struct sockaddr_in *addr_s, //ptr to addr_s
                socklen_t *size_s)          //ptr to server addr size
{
    if ((*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("open socket to clients");
        return -1;
    }

    if (bind(*sock, (struct sockaddr *)addr_s, *size_s) == -1) {
        perror("bind server socket");
        return -1;
    }

    return 0;
}