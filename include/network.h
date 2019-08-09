#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <netinet/udp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <logic.h>

#define NO_FLAGS 0
#define NUM_CLIENTS 4

#define STR_LEN 10

#define PORT_LENGTH 6
#define IP_LENGTH 17

struct msg_to_thr_s {
    struct sockaddr cli_addr;
    int *cli_count;
};

void Get_IP(char *auto_ip,                  //auto IP
            char *server_ip);               //returned IP-str

void Get_Port(char *auto_port,              //auto Port
              char *server_port);           //returned Port-str

int Init_Server(int *sock,                  //ptr to socket
                struct sockaddr_in *addr_s, //ptr to addr_s
                socklen_t *size_s);         //ptr to server addr size

int Connect_To_Server(int *sock,               //ptr to socket
                      struct sockaddr_in *addr,//filled struct
                      socklen_t *size);        //counted size

void Connect_To_Client(int sock,                //socket
                      struct sockaddr_in *addr, //filled struct
                      socklen_t *size,          //counted size
                      int num_client,           //number of waiting client
                      int *count_client);       //count of connected clients

void *Thread_Server(void *arg);

void Send(int sock,                         //socket
          struct sockaddr_in *addr,         //data for connect
          socklen_t *size,                  //counted size
          char **map,                       //double-ptr to map
          struct bullet_s *bullets,           //ptr to bullets
          struct tank_s *tanks);              //ptr to tanks

void Recv(int sock,                         //socket
          struct sockaddr_in *addr,         //data for connect
          socklen_t *size,                  //counted size
          char **map,                       //double-ptr to map
          struct bullet_s *bullets,           //ptr to bullets
          struct tank_s *tanks);              //ptr to tanks

#endif // !__NETWORK_H__
