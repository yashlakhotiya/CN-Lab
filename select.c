#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<netinet/in.h>

int main(){
	int server_socket,client_socket;
	struct sockaddr_in cliaddr, servaddr;
	fd_set readfds, testfds;

	int clilen;
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(10200);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	server_socket = socket(AF_INET,SOCK_STREAM,0);
	bind(server_socket,(struct sockaddr*)&server_socket,sizeof(server_socket));
	listen(server_socket,5);

	FD_ZERO(&readfds);
	FD_SET(server_socket,&readfds);

	while(1){
		char ch;
		int nread;
		int result = select(FD_SETSIZE,&readfds,(fd_set *)0,(fd_set *)0,(struct timeval *)0);
		if(result < 0){
			perror("ERROR\n");
			exit(1);
		}
		else{
			int fd;
			for(fd = 0; fd < FD_SETSIZE; fd++){
				if(FD_ISSET(fd,&readfds)){
					if(fd == server_socket){
						client_socket = accept(server_socket,(struct sockaddr*)&cliaddr,&clilen);
						FD_SET(client_socket,&readfds);
					}
					else{
						ioctl(fd,FIONREAD,&nread);
						if(nread == 0){
							close(fd);
							FD_CLR(fd,&readfds);
						}
						else{
							read(fd,&ch,sizeof(char));
							ch++;
							write(fd,&ch,sizeof(char));
						}
					}
				}
			}
		}
	}
}