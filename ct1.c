#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main(){
	int cli_sock;
	cli_sock = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(10200);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int n = connect(cli_sock,(struct sockaddr*)&server,sizeof(server));
	char buf[256];
	scanf("%s",buf);
	int m = write(cli_sock,buf,strlen(buf));
	close(cli_sock);
}