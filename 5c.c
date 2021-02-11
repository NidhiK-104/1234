#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void eco_cli(int sockfd)
{
	int bufsize=1024,n;
	char *buffer=malloc(bufsize);
	
	while((n=fgets(buffer,bufsize,stdin))!=NULL)
	{
		send(sockfd,buffer,bufsize,0);
		if((n=recv(sockfd,buffer,bufsize,0))>0)
		{
		printf("Server replied:");
		fputs(buffer,stdout);
		printf("\n");
		}
	}
}

int main(int argc, char *argv[])
{
	int sockfd,addrlen;
	struct sockaddr_in addr;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	addr.sin_port=htons(15001);
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	for(;;){
		int addrlen=sizeof(addr);
		connect(sockfd,(struct sockaddr*)&addr,addrlen);
		eco_cli(sockfd);
	}
}
