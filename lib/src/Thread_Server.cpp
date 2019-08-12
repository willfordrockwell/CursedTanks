#include <network.h>

void *Thread_Server (void *arg)
{
    extern pthread_mutex_t create_thread;
    extern pthread_mutex_t check_info;

    int sock;
    int ret;
    int cli_number;
    char cli_count_str[STR_LEN];

    struct info_to_server_s info_from_player;
    struct sockaddr_in recv;
    socklen_t recv_len = sizeof(recv);

    struct msg_to_thr_s msg;
    memcpy(&msg, arg, sizeof(msg));

    ret = Init_Socket(&sock, &(msg.serv_addr), &recv_len);
    if (ret == -1) {
		pthread_mutex_unlock(&create_thread);
        pthread_exit(0);
    }
    //telling to player its count number
    cli_number = *(msg.cli_count);
    sprintf(cli_count_str, "%d", cli_number);
    sendto(sock, cli_count_str, strlen(cli_count_str), MSG_CONFIRM, 
           (struct sockaddr *)&(msg.cli_addr[cli_number]),
           msg.cli_size[cli_number]);

    //making info, that we got a new player
    *(msg.cli_count) = *(msg.cli_count) + 1;

    //unlock mutex and continue Server's main
    pthread_mutex_unlock(&create_thread);
    //wait for all connecned players
    while(*(msg.cli_count) < NUM_CLIENTS) printf("%d's Waiting...", cli_number);
    //begin game
    //get info about all players
    memcpy(&msg, arg, sizeof(msg));
    //send to player map
    ret = Send_To_Player(sock, msg.cli_addr[cli_number],
                         msg.cli_size[cli_number], msg.info);
    if (ret == -1) {
        pthread_exit(0);
    }
    //the game
    while (msg.info->tanks[cli_number].health != 0) {
        //recv message from player
        ret = Recv_From_Player(sock, &info_from_player);
        if (ret == -1) {
            continue;
        }
        //critical section IN
        pthread_mutex_lock(&check_info);
        Update_Info(msg.info, &info_from_player);
        //send to other players
        for(int i = 0; i < NUM_CLIENTS; i++) {
            if (i == cli_number)
                continue;
            Send_To_Player(sock, msg.cli_addr[i], msg.cli_size[i], msg.info);
        }
        //critical section OUT
        pthread_mutex_unlock(&check_info);
    }
    //the endgame for player
    pthread_exit(0);
}
