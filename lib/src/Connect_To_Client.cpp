#include <network.h>

void Connect_To_Client(int sock,                 //socket
                       struct sockaddr_in serv,  //sockaddr
                       int *count_client,        //count of connected clients
                       struct msg_to_thr_s *msg) //ptr to info about game
{
    char buff[STR_LEN];

    int thr_sock = 0;
    int ret;
    pthread_t tid;
    extern pthread_mutex_t create_thread;

    struct sockaddr_in addr;
    socklen_t size = sizeof(addr);

    do {
        bzero(buff, STR_LEN);
        recvfrom(sock, buff, 255, MSG_WAITALL, (struct sockaddr *)&addr, &size);
    } while (strcmp(buff, "Start") != 0);

    //send to client new port in network order
    ret = Init_Socket(&thr_sock, &serv, &size);
    if (ret == -1) {
        return;
    }

    bzero(buff, STR_LEN);
    sprintf(buff, "%d", serv.sin_port);
    ret = sendto(sock, buff, strlen(buff), MSG_CONFIRM,
                 (struct sockaddr *)&addr, size);
    if (ret != strlen(buff)) {
        return;
    }
    pthread_mutex_lock(&create_thread);
    memcpy(&(msg->cli_addr[*count_client]), &addr, size);
    msg->socket = thr_sock;
    msg->cli_count = count_client;
    msg->cli_size[*count_client] = size;

    pthread_create(&tid, NULL, Thread_Server, msg);
    //wait for new thread's unlock
    pthread_mutex_lock(&create_thread);
    pthread_mutex_unlock(&create_thread);
    return;
}
