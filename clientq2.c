#include "header.h"

int CreateClientSocket(char ip_address[],int portno,struct sockaddr_in ser_addr){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(portno);
	ser_addr.sin_addr.s_addr = inet_addr(ip_address);
	connect(sockfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
	return sockfd;
}

void PerformClientTask(int sockfd){
	char buf[256];
	read(sockfd,buf,sizeof(buf));
	puts(buf);
	puts("Time is:");
	printf("%s\n",buf);
}

void TerminateSocket(int sockfd){
	close(sockfd);
	exit(0);
}

int main(){
	char ip_address[20] = IPADDRESS;
	int portno = PORTNO;
	struct sockaddr_in ser_addr;
	int sockfd = CreateClientSocket(ip_address,portno,ser_addr);
	PerformClientTask(sockfd);
	TerminateSocket(sockfd);
}