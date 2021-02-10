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
	int pid,cfd,lfd,n1,n2,n3,n,fd;char arr[100];
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
//	n1=sizeof(struct sockaddr_in);
//	while(1){

		cfd=accept(lfd,(struct sockaddr *)NULL,NULL);
//		int i=getpeername(cfd,(struct sockaddr *)&caddr,&n3);
		if(cfd==0)
		{printf("Failed..\n");exit(0);}
	//	printf("\nThe client %s is connected on port %d..\n",inet_ntoa(caddr.sin_addr),htons(caddr.sin_port));
		else {printf("\nClient connected\n");}
		while(1){		
			n=recv(cfd,arr,50,0);
			arr[n]='\0';
			if(strcmp(arr,"end")==0)
			{close(cfd);
				close(lfd);
				exit(0);}
			else{
				printf("\nCommand received:%s",arr);
				system(arr);
				printf("\n");}
	}
	return close(lfd);
}
