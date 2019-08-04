#include "CursedTanks/include/network.h"
//Должно поступать в функцию
int client_fd;
struct sockaddr_in server;
int size;

int Connect_server(int client_fd, struct sockaddr_in server, int size)
{


	char buff[255];
	int size = sizeof(struct sockaddr_in);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.1.2");
	server.sin_port = htons(5000);


	if(client_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)==-1){
		perror("open client socket");
		return 0;
	}
	sendto(client_fd, buff, 255, 0, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
	recvfrom(client_fd, buff, 255, 0, (struct sockaddr*)&server, &size);
	return 1;
}




void Send_to_server(int server_fd, struct sockaddr_in server, //data for connect
		char **map,            //double-ptr to map
        struct bullet bullet, //ptr to bullet
        struct tank tanks)
{
	int size_buff=sizeof(char*60*60)+sizeof(struct bullet)+sizeof(struct tank);
	char *buff=malloc(size_buff);

	memcpy(buff, map, sizeof(char*60*60));
	memcpy(buff+sizeof(char*60*60), &bullet, sizeof(struct bullet);
	memcpy(buff+sizeof(char*60*60) + sizeof(struct bullet), &tanks, sizeof(struct tank);

	sendto(server_fd, buff, size_buff, 0, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
}

void Get_from_server(int server_fd, struct sockaddr_in server, int size, //data for connect
		char **map,            //double-ptr to map
		struct bullet bullet, //ptr to bullet
		struct tank tanks)
{
	int size_buff=sizeof(char*60*60)+sizeof(struct bullet)+sizeof(struct tank);
	char* buff = malloc(size_buff);
	recvfrom(server_fd, buff, size_buff, 0, (struct sockaddr*)&server, &size);

	memcpy(&map, buff, sizeof(char*60*60));
	memcpy(&bullet, buff+sizeof(char*60*60), sizeof(struct bullet));
	memcpy(&tanks, buff+sizeof(char*60*60) + sizeof(struct bullet), sizeof(struct tank));
}
