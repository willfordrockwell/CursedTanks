#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <netinet/udp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <malloc.h>
#include <string.h>

#include <logic.h>

#define NO_FLAGS 0
#define NUM_CLIENTS 4

int Init_Server(int *sock,                  //ptr to socket
                struct sockaddr_in *addr_s, //ptr to addr_s
                socklen_t *size_s);         //ptr to server addr size

int Connect_To_Server(int *sock,              //ptr to socket
                     struct sockaddr_in *addr,//filled struct
                     socklen_t *size);        //counted size

int Connect_To_Client(int sock,                //socket
                     struct sockaddr_in *addr,//filled struct
                     socklen_t *size);        //counted size

void Send(int sock,                         //socket
          struct sockaddr_in *addr,         //data for connect
          socklen_t *size,                  //counted size
          char **map,                       //double-ptr to map
          struct bullet *bullets,           //ptr to bullets
          struct tank *tanks);              //ptr to tanks

void Recv(int sock,                         //socket
          struct sockaddr_in *addr,         //data for connect
          socklen_t *size,                  //counted size
          char **map,                       //double-ptr to map
          struct bullet *bullets,           //ptr to bullets
          struct tank *tanks);              //ptr to tanks

#endif // !__NETWORK_H__
