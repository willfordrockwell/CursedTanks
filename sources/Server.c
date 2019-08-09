#include <server.h>

pthread_mutex_t create_thread;
pthread_mutex_t chech_info;

int main(int argc, char const *argv[])
{
    //inits
    int sock;
    int ret;
    char buff[255];
    char str_port[PORT_LENGTH];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t serv_len = sizeof(serv_addr), cli_len = sizeof(cli_addr);

    pthread_mutex_init(&create_thread, NULL);
    pthread_mutex_init(&chech_info, NULL);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    //init port and show
    Get_Port("12345", str_port);
    serv_addr.sin_port = htons(atoi(str_port));

    ret = Init_Server(&sock, &serv_addr, &serv_len);
    if (ret == -1) {
        fprintf(stderr, "Error init server\n");
        return -1;
    }

    printf("Port to connect %d\n", htons(serv_addr.sin_port));

    //init players
    int cntd_clients = 0;
    for(int client = 0; client < NUM_CLIENTS; client++) {
        Connect_To_Client(sock, &cli_addr, &cli_len, client, &cntd_clients);
    }

    close(sock);
    return 0;
}
