#include <server.h>

pthread_mutex_t recv_msg;

int main(int argc, char const *argv[])
{
    char serv_ip[IP_LENGTH];
    char serv_port[PORT_LENGTH];
    struct sockaddr_in serv;
    socklen_t serv_len = sizeof(serv);

    int sock;
    int number;
    int ret;

    const int size_buff = SIZE_MAP + SIZE_BULLETS + SIZE_TANKS;

    char buff[size_buff];

    pthread_t tid;

    struct info_to_player_s info;
    struct info_to_server_s sending;
    struct msg_to_recv_s msg;

    pthread_mutex_init(&recv_msg, NULL);

    //get info to connect server
    Get_IP("127.0.0.1", serv_ip);
    Get_Port("12345", serv_port);

    serv.sin_family = AF_INET;
    inet_pton(AF_INET, serv_ip, &(serv.sin_addr.s_addr));
    serv.sin_port = htons(atoi(serv_port));

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        perror("create socket");
        return -1;
    }
    //connect to server's thread
    ret = Connect_To_Server(&sock, &serv, &serv_len, &number);
    if (ret == -1) {
        perror("connect to server");
        return 0;
    }
    sending.cli_num = number;
    //get start info
    msg.socket = sock;
    msg.info = &info;

    if (recvfrom(msg.socket, buff, size_buff, MSG_WAITALL,
                 (struct sockaddr *)&serv, &serv_len) < 1) {
                    perror("recv message from server");
                    return 0;
    }
    memcpy(&(msg.info->map), buff, SIZE_MAP);
    memcpy(&(msg.info->tanks), buff + SIZE_MAP, SIZE_TANKS);
    memcpy(&(msg.info->bullets), buff + SIZE_MAP + SIZE_TANKS, SIZE_BULLETS);
    //create recv thread
    pthread_create(&tid, NULL, Recv_From_Server, &msg);
    //game loop
    while (1) {
        //input
        //filling info
        //MAY BE IN INPUT FILL IN SENDING???????
        pthread_mutex_lock(&recv_msg);
        memcpy(&(sending.map), &(info.map),
               SIZE_MICRO_MAP_X * SIZE_MACRO_MAP_Y);
        memcpy(&(sending.tank), &(info.tanks[number]), sizeof(struct tank_s));
        memcpy(&(sending.bullet), &(info.bullets[number]),
               sizeof(struct bullet_s));
        if (info.tanks[number].health > 0)
            Send_To_Server(sock, &serv, &serv_len, &sending);
        pthread_mutex_unlock(&recv_msg);
        //draw
    }
    pthread_exit(0);
}
