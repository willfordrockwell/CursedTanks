
#include "CursedTanks/include/network.h"
//Должно поступать в функцию
int client_fd[4]
struct client[4];
int size[4];


int Connect_client(int *client_fd, struct sockaddr_in *client, int *size)
{
	struct sockaddr_in server;
	int serv_fd;
	char buff[255];
	

	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.1.2");
	server.sin_port = htons(5000);
	
	if(serv_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)==-1){
		perror("open server socket"); 
	}
	bind(serv_fd, (struct sockaddr*)&server, sizeof(server));
	listen(serv_fd, 5);
	

	for(int i; i<4; i++){
		
		size[i] =sizeof(struct sockaddr_in);
		client[i].sin_family = AF_INET;
		client[i].sin_addr.s_addr = htonl(INADDR_ANY);
		client[i].sin_port = htons(5000);
		
		if(client_fd[i] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)==-1){
			perror("open client socket"); 
		}
		recvfrom(client_fd[i], buff, 255, 0, (struct sockaddr*)&client[i], &size);
		sendto(client_fd[i], buff, 255, 0, (struct sockaddr*)&client[i], sizeof(struct sockaddr_in));



}

void Send_to_client(int client_fd, struct sockaddr_in client, //data for connect
		char **map,            //double-ptr to map
        struct bullet bullet, //ptr to bullet
        struct tank tanks)
{
	int size_buff=sizeof(char*60*60)+(sizeof(struct bullet)+sizeof(struct tank));
	char *buff=malloc(size_buff);
	
	memcpy(buff, map, sizeof(char*60*60));
	memcpy(buff+sizeof(char*60*60), &bullet, sizeof(struct bullet);
	memcpy(buff+sizeof(char*60*60) + sizeof(struct bullet), &tanks, sizeof(struct tank);
	
		sendto(client_fd, buff, size_buff, 0, (struct sockaddr*)&client, sizeof(struct sockaddr_in));	
}

void Get_from_client(int client_fd, struct sockaddr_in client, int size, //data for connect
		char **map,            //double-ptr to map
		struct bullet bullet, //ptr to bullet
		struct tank tanks)
{
	int size_buff=sizeof(char*60*60)+sizeof(struct bullet)+sizeof(struct tank);
	char* buff = malloc(size_buff);
		recvfrom(client_fd, buff, size_buff, 0, (struct sockaddr*)&client, &size);
	
	memcpy(&map, buff, sizeof(char*60*60));
	memcpy(&bullet, buff+sizeof(char*60*60), sizeof(struct bullet));
	memcpy(&tanks, buff+sizeof(char*60*60) + sizeof(struct bullet), sizeof(struct tank));	
}


