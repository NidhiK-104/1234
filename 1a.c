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
	int addrlen,sid,nsid,n,fd;
	char *buf=malloc(1024);
	struct sockaddr_in addr;
	char fname[256];
	if((sid=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("\nSocket created succcessfully...\n");
	else{
		printf("\nFailed to create the socket...\n");
		exit(0);
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(15432);
	addr.sin_addr.s_addr=INADDR_ANY;
	if(bind(sid,(struct sockaddr *)&addr,sizeof(addr))==0){
		printf("\nBind successful...\n");
	}
	else{
		printf("\nBind failed..\n");exit(0);}
	listen(sid,3);
	printf("\nServer listening...\n");
	addrlen=sizeof(struct sockaddr_in);
	nsid=accept(sid,(struct sockaddr *)&addr,&addrlen);
	if(nsid>0)
		printf("\nClient is connected...\n");
	else{
		printf("\nConnection failed...\n");
		exit(0);
	}
	bzero(buf,1024);
	recv(nsid,fname,256,0);
	printf("\nRequest for filename %s received..\n",fname);
	fd=open(fname,O_RDONLY);
	if((fd<0)){
		printf("\nFailed to open the requested file %s\n",fname);
		exit(0);
	}
	else{
		printf("Reading the contents of the file...\nSending the contents of the file...\n");
		while(n=read(fd,buf,1024)>0){
			//write(1,buf,n);
			printf("\n%s\nn=%d",buf,n);
			printf("\nsizeof=%d\nstr=%d\n",sizeof(buf),strlen(buf));
			send(nsid,buf,strlen(buf),0);
		}
	}
	printf("\nRequest completed...\n");
	close(nsid);
	return close(sid);
}

