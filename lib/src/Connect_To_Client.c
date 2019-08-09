#include <network.h>

void Connect_To_Client(int sock,                //socket
                      struct sockaddr_in *addr, //filled struct
                      socklen_t *size,          //counted size
                      int num_client,           //number of waiting client
                      int *count_client)        //count of connected clients
{
    char buff[255];

    pthread_t tid;
    extern pthread_mutex_t create_thread;
    struct msg_to_thr_s msg;

    do {
        recvfrom(sock, buff, 255, MSG_WAITALL, (struct sockaddr*)addr, size);
    } while (strcmp(buff, "Start") != 0);

    memcpy(&(msg.cli_addr), addr, *size);
    msg.cli_count = count_client;

    pthread_create(&tid, NULL, Thread_Server, (void *)&msg);
    pthread_mutex_lock(&create_thread);
    //wait for new thread's unlock
    pthread_mutex_lock(&create_thread);
    pthread_mutex_unlock(&create_thread);
}
