#include <network.h>

int Connect_To_Server(int *sock,                 //ptr to socket
                      struct sockaddr_in *addr,  //filled struct
                      socklen_t *size,           //counted size
                      char *number)              //ptr to number of client
{
    char buff[STR_LEN];

    if ((*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("open socket to server");
        return -1;
    }

    strcpy(buff, "Start");
    if (sendto(*sock, buff, strlen(buff), MSG_CONFIRM, (struct sockaddr *)addr,
               *size) == -1) {
                perror("Error send connect to server");
                return -1;
    }
    if (recvfrom(*sock, buff, STR_LEN, MSG_WAITALL, (struct sockaddr *)addr,
                 size) < 1) {
                    perror("Error recv connect to server");
                    return -1;
    }
    *number = atoi(buff);
    return 0;
}
