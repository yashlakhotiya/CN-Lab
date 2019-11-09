#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORTNO 10200
#define IPADDRESS "127.0.0.1"

int CreateClientSocket(char ip_address[],int portno,struct sockaddr_in ser_addr){
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(portno);
	ser_addr.sin_addr.s_addr = inet_addr(ip_address);
	connect(sockfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
	return sockfd;
}

void PerformClientTask(int sockfd){
	char buf;
	puts("Enter message:");
	scanf("%c",&buf);
	write(sockfd,&buf,sizeof(char));
	read(sockfd,&buf,sizeof(char));
	printf("%c\n",buf);
}

void TerminateSocket(int sockfd){
	close(sockfd);
	exit(0);
}

int main(){
	char ip_address[20] = "127.0.0.1";
	int portno = 10200;
	struct sockaddr_in ser_addr;
	int sockfd = CreateClientSocket(ip_address,portno,ser_addr);
	PerformClientTask(sockfd);
	TerminateSocket(sockfd);
}


