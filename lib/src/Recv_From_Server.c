#include <network.h>

void *Recv_From_Server(void *arg)
{
    extern pthread_mutex_t recv_msg;
    struct msg_to_recv_s msg;
    memcpy(&msg, arg, sizeof(msg));
    struct sockaddr_in addr;
    socklen_t size = sizeof(addr);

    const int size_buff = SIZE_MAP + SIZE_TANKS + SIZE_BULLETS;

    char buff[size_buff];

    while(1) {
        if (recvfrom(msg.socket, buff, size_buff, MSG_WAITALL,
            (struct sockaddr *)&addr, &size) < 1) {
                perror("Error recv message from server");
        }
        pthread_mutex_lock(&recv_msg);
        memcpy(&(msg.info->map), buff, SIZE_MAP);
        memcpy(&(msg.info->tanks), buff + SIZE_MAP, SIZE_TANKS);
        memcpy(&(msg.info->bullets), buff + SIZE_MAP + SIZE_TANKS,
               SIZE_BULLETS);
        pthread_mutex_unlock(&recv_msg);
    }
}
