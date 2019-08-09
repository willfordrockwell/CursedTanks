#include <network.h>

void *Thread_Server (void *arg) 
{
    extern pthread_mutex_t create_thread;
    extern pthread_mutex_t check_info;

    int sock;
    int ret;
    char cli_count_str[STR_LEN];

    struct msg_to_thr_s msg;
    memcpy(&msg, arg, sizeof(msg));

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //telling to player its count number
    sprintf(cli_count_str, "%d", *(msg.cli_count));
    sendto(sock, cli_count_str, strlen(cli_count_str), MSG_CONFIRM, 
           (struct sockaddr *)&(msg.cli_addr), msg.cli_size);

    //making info, that we got a new player
    *(msg.cli_count) = *(msg.cli_count) + 1;

    //unlock mutex and continue Server's main
    pthread_mutex_unlock(&create_thread);
    //wait for all connecned players
    while(*(msg.cli_count) < NUM_CLIENTS);
    //begin game
    //send to thread's player map
    ret = Send_To_Player(sock, &(msg.cli_addr), &(msg.cli_size), msg.msg);
    if (ret == -1) {
        pthread_exit(0);
    }
}