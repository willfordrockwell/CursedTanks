#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <netinet/udp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <logic.h>

#define NO_FLAGS 0
#define NUM_CLIENTS 4

#define STR_LEN 10

#define PORT_LENGTH 6
#define IP_LENGTH 17

struct info_to_server_s {
    char map[SIZE_MICRO_MAP_Y][SIZE_MICRO_MAP_X];
    struct tank_s tank;
    struct bullet_s bullet;
};

struct info_to_player_s {
    char map[SIZE_MICRO_MAP_Y][SIZE_MICRO_MAP_X];
    struct tank_s tanks[NUM_CLIENTS];
    struct bullet_s bullets[NUM_CLIENTS];
};

struct msg_to_thr_s {
    struct sockaddr_in cli_addr;
    socklen_t cli_size;
    int *cli_count;
    struct info_to_player_s *msg;
};

void Get_IP(char *auto_ip,                  //auto IP
            char *server_ip);               //returned IP-str

void Get_Port(char *auto_port,              //auto Port
              char *server_port);           //returned Port-str

int Init_Server(int *sock,                  //ptr to socket
                struct sockaddr_in *addr_s, //ptr to addr_s
                socklen_t *size_s);         //ptr to server addr size

int Connect_To_Server(int *sock,                //ptr to socket
                      struct sockaddr_in *addr, //filled struct
                      socklen_t *size,          //counted size
                      int *number);             //ptr to number of client

void Connect_To_Client(int sock,                 //socket
                       int num_client,           //number of waiting client
                       int *count_client,        //count of connected clients
                       struct msg_to_thr_s *msg);//ptr to info about game

void *Thread_Server(void *arg);

int Send_To_Player(int sock,                         //socket
                   struct sockaddr_in *addr,         //data for connect
                   socklen_t *size,                  //counted size
                   struct info_to_player_s *info);   //ptr to info

int Recv_From_Server(int sock,                      //socket
                     struct sockaddr_in *addr,      //data for connect
                     socklen_t *size,               //counted size
                     struct info_to_player_s *info);//ptr to info

#endif // !__NETWORK_H__
