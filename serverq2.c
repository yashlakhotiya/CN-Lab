#include "header.h"
#include<time.h>

int createServerSocket(char ip_address[],int portno,struct sockaddr_in seraddr){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(10200);
	seraddr.sin_addr.s_addr = inet_addr(ip_address);

	bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	listen(sockfd,5);
	return sockfd;
}

int performServerTask(int sockfd,struct sockaddr_in cliaddr){
	int clilen = sizeof(clilen);
	int newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
	time_t tick;
	time(&tick);
	char time[256];
	sprintf(time,ctime(&tick));
	write(newsockfd,time,strlen(time));
}

void TerminateSocket(int sockfd,int newsockfd){
	close(sockfd);
	close(newsockfd);
	exit(0);
}

int main(){
	char ip_address[20] = IPADDRESS;
	int portno = PORTNO;
	struct sockaddr_in ser_addr,cli_addr;
	int sockfd = createServerSocket(ip_address,portno,ser_addr);
	int newsockfd = performServerTask(sockfd,cli_addr);
	TerminateSocket(sockfd,newsockfd);
}