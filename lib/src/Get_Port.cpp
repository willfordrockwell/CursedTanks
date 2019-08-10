#include <network.h>

void Get_Port(char *auto_port,
              char *server_port)
{
    printf("Enter server port (auto: %s): ", auto_port);
    fgets(server_port, PORT_LENGTH, stdin);
    if (strncmp(server_port, "", 1)) {
        strcpy(server_port, auto_port);
    }
}