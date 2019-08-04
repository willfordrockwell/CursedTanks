#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<string.h>
#include <netinet/udp.h>
#include <malloc.h>

int Connect_server(int client_fd, struct sockaddr_in server, int size);

void Send_to_server(int server_fd, struct sockaddr_in server, //data for connect
		char **map,            //double-ptr to map
        struct bullet bullet, //ptr to bullet
        struct tank tanks));


void Get_from_server(int server_fd, struct sockaddr_in server, int size, //data for connect
		char **map,            //double-ptr to map
		struct bullet bullet, //ptr to bullet
		struct tank tanks));

int Connect_client(int *client_fd, struct sockaddr_in *client, int *size);


void Send_to_client(int client_fd, struct sockaddr_in client, //data for connect
		char **map,            //double-ptr to map
		struct bullet bullet, //ptr to bullet
		struct tank tanks));

void Get_from_client(int client_fd, struct sockaddr_in client, int size, //data for connect
		char **map,            //double-ptr to map
		struct bullet bullet, //ptr to bullet
		struct tank tanks));

#endif __NETWORK_H__
