#include <network.h>

void *Recv_From_Server(void *arg)
{
    extern pthread_mutex_t recv_msg;
    struct msg_to_recv_s msg;
    memcpy(&msg, arg, sizeof(msg));
    struct sockaddr_in addr;
    socklen_t size = sizeof(addr);

    const int size_buff = SIZE_MAP + SIZE_TANKS + SIZE_BULLETS;

    while(1) {
        if (recvfrom(msg.socket, (char *)msg.info, size_buff, MSG_WAITALL,
            (struct sockaddr *)&addr, &size) < 1) {
                perror("Error recv message from server");
                continue;
        }
        pthread_mutex_lock(&recv_msg);
        for (int i = 0; i < NUM_CLIENTS; i++) {
            if (i == msg.cli_num)
                continue;
            msg.tanks[i].Set_Structure(msg.info->tanks[i]);
            msg.bullets[i].Set_Structure(msg.info->bullets[i]);
        }
        for(int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
            memcpy(msg.map[i], msg.info->map[i], SIZE_MICRO_MAP_X);
        }
        pthread_mutex_unlock(&recv_msg);
    }
}
