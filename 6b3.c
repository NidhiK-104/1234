#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include<string.h>

void dg_cli(FILE *fp, int sockfd,const struct sockaddr *paddr,socklen_t slen)
{
	int bufsize = 1024000;
	char *buffer = malloc(bufsize);
	char *buf=malloc(bufsize);

	while (fgets(buffer, bufsize, fp) != NULL)
	{
		if ((strncmp(buffer, "exit", 4)) == 0)
	{
	printf("Client Exit...\n");
	
	break;
	}
		sendto(sockfd, buffer, strlen(buffer), 0,paddr,slen);  
		int n=recvfrom(sockfd, buf, bufsize, 0,NULL,NULL);
		buf[n]='\0';
		if(n>0){
		//printf("%s\n",buf);
	    	fputs(buf, stdout);
		}
	}
}


int main(int argc,char *argv[])
{
	int create_socket;
	struct sockaddr_in address;
	
	if ((create_socket = socket(AF_INET,SOCK_DGRAM,0)) > 0)
		printf("The socket was created\n");
		
	address.sin_family = AF_INET;
	address.sin_port = htons(15432);			
	inet_pton(AF_INET, argv[1], &address.sin_addr);		
		
	dg_cli(stdin, create_socket,(struct sockaddr *)&address,sizeof(address));
	exit(0);	

}
