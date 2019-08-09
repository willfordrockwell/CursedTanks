#include <server.h>

int main(int argc, char const *argv[])
{
    char serv_ip[IP_LENGTH];
    char serv_port[PORT_LENGTH];
    char cli_count_str[STR_LEN];
    struct sockaddr_in serv;
    socklen_t serv_len = sizeof(serv);
    int sock;
    int number;

    Get_IP("127.0.0.1", serv_ip);
    Get_Port("12345", serv_port);
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, serv_ip, &(serv.sin_addr.s_addr));
    serv.sin_port = htons(atoi(serv_port));
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sendto(sock, "Start", 5, MSG_CONFIRM, (struct sockaddr *)&serv,
           sizeof(serv));
    recvfrom(sock, cli_count_str, STR_LEN, MSG_WAITALL,
             (struct sockaddr *)&serv, &serv_len);
    number = atoi(cli_count_str);
    printf("recv from thread: %d\n", number);
    return 0;
}
