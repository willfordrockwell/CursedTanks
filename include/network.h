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

#define STR_LEN 10

#define PORT_LENGTH 6
#define IP_LENGTH 17

#define SIZE_MAP SIZE_MICRO_MAP_X * SIZE_MICRO_MAP_Y
#define SIZE_TANK sizeof(struct tank_s)
#define SIZE_TANKS SIZE_TANK * NUM_CLIENTS 
#define SIZE_BULLET sizeof(struct bullet_s)
#define SIZE_BULLETS SIZE_BULLET * NUM_CLIENTS
#define SIZE_CLI_NUM 1

struct msg_to_thr_s {
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr[NUM_CLIENTS];
    socklen_t cli_size[NUM_CLIENTS];
    int *cli_count;
    struct info_to_player_s *info;
};

struct msg_to_recv_s {
    int socket;
	char **map;
    struct info_to_player_s *info;
};

void Get_IP(char *auto_ip,                  //auto IP
            char *server_ip);               //returned IP-str

void Get_Port(char *auto_port,              //auto Port
              char *server_port);           //returned Port-str

int Init_Socket(int *sock,                  //ptr to socket
                struct sockaddr_in *addr,   //ptr to addr
                socklen_t *size);           //ptr to addr size

int Connect_To_Server(int *sock,                //ptr to socket
                      struct sockaddr_in *addr, //filled struct
                      socklen_t *size,          //counted size
                      int *number);             //ptr to number of client

void Connect_To_Client(int sock,                 //socket
                       struct sockaddr_in serv,  //sockaddr
                       int *count_client,        //count of connected clients
                       struct msg_to_thr_s *msg);//ptr to info about game

void *Thread_Server(void *arg);                  //ptr to msg_to_thr_s

int Send_To_Player(int sock,                         //socket
                   struct sockaddr_in addr,          //data about recv
                   socklen_t size,                   //counted size
                   struct info_to_player_s *info);   //ptr to info

int Send_To_Server(int sock,                         //socket
                   struct sockaddr_in *addr,         //data about recv
                   socklen_t *size,                  //counted size
                   struct info_to_server_s *info);   //ptr to info

void *Recv_From_Server(void *arg);

int Recv_From_Player(int sock,                       //socket
                     struct info_to_server_s *info); //ptr to info

#endif // !__NETWORK_H__
