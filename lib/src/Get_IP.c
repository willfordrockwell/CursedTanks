#include <network.h>

void Get_IP(char *auto_ip,
            char *server_ip)
{
    char no_input[1] = {'\n'};
    printf("Enter server IP (auto: %s): ", auto_ip);
    fgets(server_ip, IP_LENGTH, stdin);
    if (strcmp(server_ip, no_input) == 0) {
        strcpy(server_ip, auto_ip);
    }
}