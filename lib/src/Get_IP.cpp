#include <network.h>

void Get_IP(char *auto_ip,                  //auto IP
            char *server_ip)                //returned IP-str
{
    char no_input[1] = {'\0'};
    printf("Enter server IP (auto: %s): ", auto_ip);
    fgets(server_ip, IP_LENGTH, stdin);
    server_ip[strlen(server_ip) - 1] = '\0';
    if (strcmp(server_ip, no_input) == 0) {
        strcpy(server_ip, auto_ip);
    }
    return;
}