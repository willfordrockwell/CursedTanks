#include <server.h>

pthread_mutex_t create_thread;
pthread_mutex_t check_info;

int main(int argc, char const *argv[])
{
    //inits
    int sock;
    int ret;
    int cntd_clients = 0;
    int live_clients = NUM_CLIENTS;

    char str_port[PORT_LENGTH];

    struct sockaddr_in serv_addr;
    socklen_t serv_len = sizeof(serv_addr);

    struct info_to_player_s info;
    struct msg_to_thr_s msg;

    //fill into info map, tank, bullets
    //Load_Map(info.map);
    for (int i = 0; i < NUM_CLIENTS; i++) {
        info.tanks[i].coord.x = i * SIZE_MACRO_TILE;
        info.tanks[i].coord.y = i * SIZE_MACRO_TILE;
        info.tanks[i].direct = UP;
        info.tanks[i].health = 5;
        info.bullets[i].coord.x = -1;
        info.bullets[i].coord.y = -1;
        info.bullets[i].direct = UP;
    }
    msg.info = &info;

    pthread_mutex_init(&create_thread, NULL);
    pthread_mutex_init(&check_info, NULL);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    //init port and show
    Get_Port((char*)"12345", str_port);
    serv_addr.sin_port = htons(atoi(str_port));

    ret = Init_Socket(&sock, &serv_addr, &serv_len);
    if (ret == -1) {
        fprintf(stderr, "Error init server\n");
        return -1;
    }

    printf("Port to connect %d\n", htons(serv_addr.sin_port));

    //init players
    while(cntd_clients < NUM_CLIENTS) {
        Connect_To_Client(sock, serv_addr, &cntd_clients, &msg);
    }

    close(sock);
    while(live_clients > 1) {
        live_clients = NUM_CLIENTS;
        for (int i = 0; i < NUM_CLIENTS; i++) {
            if (info.tanks[i].health == 0) {
                live_clients--;
            }
        }
    }
    pthread_exit(0);
}
