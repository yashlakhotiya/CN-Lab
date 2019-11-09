#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
int sd;
struct sockaddr_in sadd,cadd;
sd = socket(AF_INET,SOCK_DGRAM,0);
sadd.sin_family=AF_INET;
sadd.sin_addr.s_addr=inet_addr("127.0.0.1");
sadd.sin_port=htons(10200);
int result=bind(sd,(struct sockaddr*)&sadd,sizeof(sadd));
int len=sizeof(cadd);
int msize;
int n=recvfrom(sd,&msize,sizeof(int),0,(struct sockaddr*)&cadd,&len);
int arr[msize*msize];
n=recvfrom(sd,arr,sizeof(arr),0,(struct sockaddr*)&cadd,&len);
int matrix[msize][msize];
int count = 0;
for(int i = 0;i < msize;i++){
for(int j = 0;j < msize;j++){
matrix[i][j] = arr[count];
count++;
}
}
int m=sendto(sd,matrix,sizeof(matrix),0,(struct sockaddr*)&cadd,len);
return 0;
}
