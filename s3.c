#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<ctype.h>
#include <arpa/inet.h>



int CreateServerSocket(char* ipaddress, int portno)//returns sockfd
{
	//create the struct
	struct sockaddr_in mysockstruct;

	//fill in the details
	mysockstruct.sin_family = AF_INET;
	mysockstruct.sin_addr.s_addr = inet_addr(ipaddress);
	mysockstruct.sin_port = htons(portno);

	//create socket
	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	//bind the socket with the struct
	bind(sockfd,  (struct sockaddr*)  &mysockstruct ,sizeof(mysockstruct) );


	//return the file descriptor
	return sockfd;
}

void PerformServerTask(int newsockfd, struct sockaddr_in clientsocket)
{
	char buf[256]; 
	int n;

	n=read(newsockfd,buf,sizeof(buf));
	printf("\nMessage from client is %s\n",buf);
	printf("Client IP address is: %s\n",inet_ntoa(clientsocket.sin_addr));
	printf("Client Port No. is %d\n",ntohs(clientsocket.sin_port));
	for(int i=0;i<strlen(buf);i++)
		buf[i] = toupper(buf[i]);
	//printf("UPPER: %s\n", buf);
	n=write(newsockfd,buf,sizeof(buf));

}


int main()
{
	char ipaddress[] = "127.0.0.1";
	int portno = 10200;
	


	int sockfd = CreateServerSocket(ipaddress,portno);





	struct sockaddr_in clientsocket;

	int clientlength,newsockfd;



	

	while(1)
	{
		listen(sockfd,5);
		clientlength = sizeof(clientsocket);

		newsockfd = accept(sockfd,(struct sockaddr *)&clientsocket,&clientlength);

		PerformServerTask(newsockfd, clientsocket);

	}




	return 0;
}