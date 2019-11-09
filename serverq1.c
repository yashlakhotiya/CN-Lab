#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORTNO 10200
#define IPADDRESS "127.0.0.1"

int CreateServerSocket(char ip_address[],int portno,struct sockaddr_in ser_addr){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(portno);
	ser_addr.sin_addr.s_addr = inet_addr(ip_address);

	bind(sockfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
	listen(sockfd,5);
	return sockfd;
}

int PerformServerTask(int sockfd,struct sockaddr_in cliaddr){
	char buf[256];
	int clilen = sizeof(cliaddr);
	int newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
	printf("PORT NO OF CLIENT IS %d\n",ntohs(cli_addr));
	read(newsockfd,buf,sizeof(buf));
	puts("Message from client is:");
	printf("%s\n",buf);
	return newsockfd;
}

void TerminateSocket(int sockfd,int newsockfd){
	close(sockfd);
	close(newsockfd);
	exit(0);
}

int main(){
	char ip_address[20] = "127.0.0.1";
	int portno = 10200;
	struct sockaddr_in ser_addr,cli_addr;
	int sockfd = CreateServerSocket(ip_address,portno,ser_addr);
	int newsockfd = PerformServerTask(sockfd,cli_addr);
	TerminateSocket(sockfd,newsockfd);
}
