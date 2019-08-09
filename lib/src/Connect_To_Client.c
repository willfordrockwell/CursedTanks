#include <network.h>

void Connect_To_Client(int sock,                 //socket
                       int num_client,           //number of waiting client
                       int *count_client,        //count of connected clients
                       struct msg_to_thr_s *msg) //ptr to info about game
{
    char *buff = (char *) malloc(sizeof(char) * 255);

    pthread_t tid;
    extern pthread_mutex_t create_thread;

    struct sockaddr_in addr;
    socklen_t size;

    do {
        recvfrom(sock, buff, 255, MSG_WAITALL, (struct sockaddr *)&addr, &size);
    } while (strcmp(buff, "Start") != 0);
    free(buff);

    memcpy(&(msg->cli_addr), &addr, size);
    msg->cli_count = count_client;
    msg->cli_size = size;

    pthread_create(&tid, NULL, Thread_Server, (void *)msg);
    pthread_mutex_lock(&create_thread);
    //wait for new thread's unlock
    pthread_mutex_lock(&create_thread);
    pthread_mutex_unlock(&create_thread);
}
