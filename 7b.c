#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int create_socket;
	struct sockaddr_in address;
	char cmd[100];
	if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
		printf("The socket was created\n");
		
	address.sin_family = AF_INET;
	address.sin_port = htons(15432);			
	inet_pton(AF_INET, argv[1], &address.sin_addr);	
	
	if (connect(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
		printf("The connection was accepted with the server %s...\n",argv[1]);
	else
		{printf("Error in connect\n");	exit(0);}		
		
		while(1){
			printf("\nEnter the command:");gets(cmd);	
			if(strcmp(cmd,"end")!=0){
				send(create_socket,cmd,50,0);}
			else{
				send(create_socket,cmd,50,0);close(create_socket);break;}			
}
}
