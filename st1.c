#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){
	int serv_sock;
	serv_sock = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server,client;
	server.sin_family = AF_INET;
	server.sin_port = htons(10200);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(serv_sock,(struct sockaddr*)&server,sizeof(server));
	listen(serv_sock,5);
	while(1){
		char buf[256];
		//printf is not working
		puts("\nServer waiting");
		int clilen = sizeof(client);
		int cli_sock = accept(serv_sock,(struct sockaddr*)&client,&clilen);

		int n = read(cli_sock,buf,sizeof(buf));

		puts("\nMessage from client is: ");

		printf("%s\n",buf);

		close(cli_sock);
	}
}