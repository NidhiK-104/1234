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
void str_echo(int cfd,struct sockaddr* caddr,int clen){
	int n,max=255000000,len;
	char *buf=malloc(max);
	while(1){
		len=clen;
		n=recvfrom(cfd,buf,max,0,caddr,&len);
		sendto(cfd,buf,n,0,caddr,len);
	}
}	
int main(int argc, char* argv[]){
	int pid,cfd,lfd,n1,n2,n3,n,fd;
	struct sockaddr_in caddr,addr;
	if((lfd=socket(AF_INET,SOCK_DGRAM,0))>0)
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
	
			str_echo(lfd,(struct sockaddr *)&caddr,sizeof(caddr));
	return 0;
}
