#include <server.h>
#include <map.h>
#include <map_func.h>

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

	char **tmp_map;
	tmp_map =(char** ) malloc(sizeof(char*) * SIZE_MICRO_MAP_Y);
	for (int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
		tmp_map[i] = (char* ) malloc(sizeof(char) * SIZE_MICRO_MAP_X);
	}
    //fill into info map, tank, bullets
    Macro_To_Micro(macro_tile, tmp_map);
	for(int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
		for(int j = 0; j < SIZE_MICRO_MAP_X; j++){
			info.map[i][j] = tmp_map[i][j];
		}
	}
	info.tanks[0].coord.x = 48;
	info.tanks[0].coord.y = 16;
	info.tanks[0].direct = UP;
	info.tanks[0].health = 5;
	info.tanks[1].coord.x = 80;
	info.tanks[1].coord.y = 16;
	info.tanks[1].direct = UP;
	info.tanks[1].health = 5;
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
