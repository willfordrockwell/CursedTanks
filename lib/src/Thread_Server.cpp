#include <network.h>

void *Thread_Server (void *arg)
{
    extern pthread_mutex_t create_thread;
    extern pthread_mutex_t check_info;

    int ret;
    int cli_number;
    char buff[STR_LEN];
    char cli_count_str[STR_LEN];
    struct info_to_server_s info_from_player;

    struct sockaddr_in addr_in;
    socklen_t size = sizeof(addr_in);

    struct msg_to_thr_s msg;
    memcpy(&msg, arg, sizeof(msg));

    //counting for player its count number
    cli_number = *(msg.cli_count);
    sprintf(cli_count_str, "%d", cli_number);

    //waiting new client
    do {
        recvfrom(*(msg.socket), buff, STR_LEN, MSG_WAITALL,
                 (struct sockaddr *)&msg.cli_addr[cli_number],
                 &msg.cli_size[cli_number]);
    } while (strcmp(buff, "Start") != 0);

    //sending its number
    sendto(*(msg.socket), cli_count_str, strlen(cli_count_str), MSG_CONFIRM,
           (struct sockaddr *)&(msg.cli_addr[cli_number]),
           msg.cli_size[cli_number]);

    //making info, that we got a new player
    *(msg.cli_count) = *(msg.cli_count) + 1;

    //unlock mutex and continue Server's main
    pthread_mutex_unlock(&create_thread);
    //wait for all connecned players
    printf("player connected\n");
    while(*(msg.cli_count) < NUM_CLIENTS);
    //begin game
    //get info about all players
    memcpy(&msg, arg, sizeof(msg));
    //send to player map
    ret = Send_To_Player(*(msg.socket), msg.cli_addr[cli_number],
                         msg.cli_size[cli_number], msg.info);
    if (ret == -1) {
        pthread_exit(0);
    }
    //the game
    while (msg.info->tanks[cli_number].health != 0) {
        //recv message from player
        ret = Recv_From_Player(*(msg.socket), &addr_in, &size, &info_from_player);
        if (ret == -1) {
            continue;
        }
        //critical section IN
        pthread_mutex_lock(&check_info);
        Update_Info(msg.info, &info_from_player);
        //send to other players
        for(int i = 0; i < NUM_CLIENTS; i++) {
            if (addr_in.sin_addr.s_addr == msg.cli_addr[i].sin_addr.s_addr)
                continue;
            Send_To_Player(*(msg.socket), msg.cli_addr[i], msg.cli_size[i],
                           msg.info);
        }
        //critical section OUT
        pthread_mutex_unlock(&check_info);
    }
    //the endgame for player
    pthread_exit(0);
}
