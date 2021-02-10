#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<fcntl.h>
void str_echo(int cfd){
	int n,max=255000000;
	char *buf=malloc(max);
again:
	while((n=recv(cfd,buf,max,0))>0)
		send(cfd,buf,strlen(buf),0);
		if(n<0)
			goto again;
//		free(buf);
	
}	
int main(int argc, char* argv[]){
	int pid,cfd,lfd,n1,n2,n3,n,fd;
	struct sockaddr_in caddr,addr;
	if((lfd=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("\nSocket created succcessfully...\n");
	else{
		printf("\nFailed to create the socket...\n");
		exit(0);
	}
	addr.sin_family=AF_INET;
	//addr.sin_port=htons(16001);
	addr.sin_port=htons(15432);
	addr.sin_addr.s_addr=INADDR_ANY;
	int b=bind(lfd,(struct sockaddr *)&addr,sizeof(addr));
	printf("b=%d\n",b);
	if(b==0){
		printf("\nBind successful...\n");
	}
	else{
		printf("\nBind failed..\n");exit(0);}
	listen(lfd,3);
	printf("\nServer listening...\n");
	n1=sizeof(struct sockaddr_in);
//	getsockname(lfd,(struct sockaddr *)&caddr,&n2);
//	printf("\nServer's local address is %s...and port is %d\n",inet_ntoa(addr.sin_addr),htons(addr.sin_port));
	while(1){

		cfd=accept(lfd,(struct sockaddr *)&caddr,&n1);
//		int i=getpeername(cfd,(struct sockaddr *)&caddr,&n3);
		printf("\nThe client %s is connected on port %d..\n",inet_ntoa(caddr.sin_addr),htons(caddr.sin_port));
		
			str_echo(cfd);
			close(cfd);
	}
	return 0;
}
