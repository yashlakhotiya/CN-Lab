#include"header.h"
#include<ctype.h>

int CreateServerSocket(struct sockaddr_in serv_addr){
	int portno = PORTNO;
	char ip_addr[20] = IPADDRESS;

	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = inet_addr(ip_addr);

	bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	listen(sockfd,5);

	return sockfd;
}

int PerformServerTask(int sockfd,struct sockaddr_in cli_addr){
	int clilen = sizeof(cli_addr);
	int newSockfd = accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
	printf("\nIPADDR: %s\t",inet_ntoa(cli_addr.sin_addr));
	printf("\nPORTNO: %d\n",ntohs(cli_addr.sin_port));
	while(1){
		char bufr[256];
		read(newSockfd,bufr,sizeof(bufr));
		int j=0;
		while(bufr[j]!='\0'){
			bufr[j] = toupper(bufr[j]);
			//printf("%c\n",bufr[j]);
			j++;
		}
		write(newSockfd,bufr,strlen(bufr));
	}
}

void TerminateServerSocket(int sockfd){
	close(sockfd);
	exit(0);
}

int main(){
	int sockfd,newsockfd;
	struct sockaddr_in cli_addr,serv_addr;
	sockfd = CreateServerSocket(serv_addr);
	newsockfd = PerformServerTask(sockfd,cli_addr);
	TerminateServerSocket(sockfd);
}