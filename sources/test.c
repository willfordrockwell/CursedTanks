#include <network.h>

int main(int argc, char const *argv[])
{
    char serv_ip[IP_LENGTH];
    char serv_port[PORT_LENGTH];
    struct sockaddr_in serv;
    int sock;

    Get_IP("127.0.0.1", serv_ip);
    Get_Port("12345", serv_port);
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, serv_ip, &(serv.sin_addr.s_addr));
    serv.sin_port = htons(atoi(serv_port));
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sendto(sock, "Hello", 5, MSG_CONFIRM, (struct sockaddr *) &serv,
           sizeof(serv));
    return 0;
}
