#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#define group "225.0.0.35"
#define port 12345
int main(int argc,char *argv[]){
	struct sockaddr_in addr;
	char *message;
	int sid;
	if(argc==1){
		message="NIDHI K";
	}
	else message=argv[1];
	if((sid=socket(AF_INET,SOCK_DGRAM,0))<0){
		printf("\nSocket creation failed\n");
		exit(0);
	}
	else
		printf("\nSocket created successfully...\n");
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(group);
	addr.sin_port=htons(port);

	while(1){
		if((sendto(sid,message,strlen(message),0,(struct sockaddr *)&addr,sizeof(addr))<0)){
			printf("\nFailed\n");
			exit(0);
		}
		else printf("\nMessage sent successfully...\n");
		sleep(2);
	}
	return close(sid);
}


