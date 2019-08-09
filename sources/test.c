#include <server.h>

int main(int argc, char const *argv[])
{
    char serv_ip[IP_LENGTH];
    char serv_port[PORT_LENGTH];
    struct sockaddr_in serv;
    socklen_t serv_len = sizeof(serv);
    int sock;
    int number;

    struct info_to_player_s info;

    Get_IP("127.0.0.1", serv_ip);
    Get_Port("12345", serv_port);
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, serv_ip, &(serv.sin_addr.s_addr));
    serv.sin_port = htons(atoi(serv_port));
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    Connect_To_Server(&sock, &serv, &serv_len, &number);
    printf("recv from thread: %d\n", number);
    Recv_From_Server(sock, &serv, &serv_len, &info);
    for (int i = 0; i < NUM_CLIENTS; i++) {
        if (number == i)
            printf("My ");
        printf("%d's tank's coord: (%2d, %2d), direct: %d, health: %d\n", i,
               info.tanks[i].coord.x, info.tanks[i].coord.y,
               info.tanks[i].direct, info.tanks[i].health);
        if (number == i)
            printf("My ");
        printf("%d's bullet's coord: (%2d, %2d), direct: %d\n", i,
               info.bullets[i].coord.x, info.bullets[i].coord.y,
               info.bullets[i].direct);
    }
    return 0;
}
