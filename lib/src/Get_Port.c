#include <network.h>

void Get_Port(char *auto_port,              //auto Port
              char *server_port)            //returned Port-str
{
    char no_input[1] = {'\n'};
    printf("Enter server port (auto: %s): ", auto_port);
    fgets(server_port, PORT_LENGTH, stdin);
    if (strcmp(server_port, no_input) == 0) {
        strcpy(server_port, auto_port);
    }
    return;
}