#include"header.h"

int CreateClientSocket(struct sockaddr_in serv_addr)
{
	int portno = PORTNO;
	char ip_addr[20] = IPADDRESS;

	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = inet_addr(ip_addr);

	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	return sockfd;
}

void TerminateClientSocket(int sockfd){
	close(sockfd);
	exit(0);
}

void PerformClientTask(int sockfd){
	//while(1){
		char bufw[256],bufr[256];
		puts("Send some sentences");
		gets(bufw);
		//puts(bufw);
		//printf("%d\t\t%d\n",sizeof(bufw),strlen(bufw));
		if(!strcmp(bufw,"QUIT") || !strcmp(bufw,"quit")){
			close(sockfd);
			exit(0);
		}
		write(sockfd,bufw,sizeof(bufw));
		//puts("test");
		//puts(bufr);
		//puts(bufw);
		int y = read(sockfd,bufr,sizeof(bufr));
		bufr[y] = '\0';
		puts("Capitalized String sent back from server is: ");
		puts(bufr);
	//}
	//TerminateClientSocket(sockfd);
}

int main(){
	int sockfd;
	struct sockaddr_in serv_addr;
	while(1){
		sockfd = CreateClientSocket(serv_addr);
		PerformClientTask(sockfd);
	}
	TerminateClientSocket(sockfd);
	return 0;
}