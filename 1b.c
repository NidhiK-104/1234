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
int main(int argc, char* argv[]){
	int sid,n,fd;
	char *buf=malloc(1024);
	struct sockaddr_in addr;
	char fname[255];
	if((sid=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("\nSocket created succcessfully...\n");
	else{
		printf("\nFailed to create the socket...\n");
		exit(0);
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(15432);
	addr.sin_addr.s_addr=INADDR_ANY;
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	if(connect(sid,(struct sockaddr *)&addr,sizeof(addr))==0){
		printf("\nConnection accepetd by the server..\n");}
	else{
		printf("\nConnection failed...\n");
		exit(0);
	}
	printf("\nEnter the filename:");gets(fname);
	send(sid,fname,sizeof(fname),0);
	printf("Contents of the file are..\n");
	while((n=recv(sid,buf,1024,0)>0))
		//write(1,buf,n);{
		printf("\n%s\nn=%d",buf,n);
	printf("\nEOF\n");
	return close(sid);
}
