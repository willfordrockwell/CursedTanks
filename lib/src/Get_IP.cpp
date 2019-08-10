#include <network.h>

void Get_IP(char *auto_ip,
            char *server_ip)
{
    printf("Enter server IP (auto: %s): ", auto_ip);
    fgets(server_ip, IP_LENGTH, stdin);
    if (strncmp(server_ip, "", 1)) {
        strcpy(server_ip, auto_ip);
    }
}