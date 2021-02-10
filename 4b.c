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
	int sid,n;u_int yes=1;
	struct ip_mreq mreq;
	char buf[1024];
	if((sid=socket(AF_INET,SOCK_DGRAM,0))<0){
		printf("\nSocket creation failed\n");
		exit(0);
	}
	else
		printf("\nSocket created successfully...\n");
	
	if(setsockopt(sid,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes))<0){
		printf("\nReusing address failed\n");
		exit(1);
	}
	else printf("Reusing address successful\n");
	bzero(&addr,sizeof(addr));
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=htonl(INADDR_ANY);
        addr.sin_port=htons(port);

	if(bind(sid,(struct sockaddr *)&addr,sizeof(addr))<0){
		printf("\nBind failed\n");exit(0);}
	else printf("\nBind successful");
	mreq.imr_multiaddr.s_addr=inet_addr(group);
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	int sets=setsockopt(sid,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	printf("\nSets=%d\t sid=%d\n",sets,sid);
	if(sets<0){
		printf("\nError adding to multicast group\n");
		exit(0);
	}
	else printf("\nSuccessfully added to mc group\n");


	while(1){
		int len=sizeof(struct sockaddr_in);
		//if((n=recvfrom(sid,buf,sizeof(buf),0,(struct sockaddr *)&addr,&len))<0)
		if((n=recvfrom(sid,buf,sizeof(buf),0,NULL,NULL))<0){
			printf("\nFailed to receive\n");
			exit(0);
		}
		buf[n]='\0';

		printf("\nMessage received: %s\n",buf);
	}	
	return 0;
}

