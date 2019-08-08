#include <network.h>

int Init_Server(int *sock,                  //ptr to socket
                struct sockaddr_in *addr_s, //ptr to addr_s
                socklen_t *size_s)          //ptr to server addr size
{
    if ((*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("open socket to clients");
        return -1;
    }

    while (bind(*sock, (struct sockaddr *)addr_s, *size_s) == -1) {
        switch (errno)
        {
        case EACCES:
            addr_s->sin_port = htons(htons(addr_s->sin_port) + 1);
            break;
        
        default:
            return -1;
        }
    }

    return 0;
}