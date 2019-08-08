#include <server.h>

int main(int argc, char const *argv[])
{
    //inits
    int sock;
    int ret;
    char buff[255];
    char str_port[PORT_LENGTH];
    struct sockaddr_in server_in;
    socklen_t addrlen = sizeof(server_in);

    Get_Port("12345", str_port);
    server_in.sin_family = AF_INET;
    server_in.sin_addr.s_addr = INADDR_ANY;
    server_in.sin_port = htons(atoi(str_port));
    ret = Init_Server(&sock, &server_in, &addrlen);
    if (ret == -1) {
        printf("Some shit\n");
        return -1;
    }

    printf("Port to connect %d\n", htons(server_in.sin_port));

    recvfrom(sock, buff, 255, 0, (struct sockaddr*) &server_in, &addrlen);
    printf("%s\n", buff);

    close(sock);
    return 0;
}
