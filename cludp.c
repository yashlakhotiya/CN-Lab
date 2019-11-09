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
struct sockaddr_in address;
sd=socket(AF_INET,SOCK_DGRAM,0);
address.sin_family=AF_INET;
address.sin_addr.s_addr=inet_addr("127.0.0.1");
address.sin_port=htons(10200);
puts("enter size of array\n");
int size;
scanf("%d",&size);
puts("\nenter size of matrix\n");
int msize;
puts("enter array elements row by row\ntype -1 to exit");
scanf("%d",&msize);
int m=sendto(sd,&msize,sizeof(int),0,(struct sockaddr*)&address,sizeof(address));
int arr[size];
puts("\nenter elements\n");
int ele;
for(int i = 0;i < size;i++){
scanf("%d",&ele);
arr[i] = ele;
}
int matrix[msize][msize];
int len = sizeof(address);
m=sendto(sd,arr,sizeof(arr),0,(struct sockaddr*)&address,len);
int n=recvfrom(sd,matrix,sizeof(matrix),0,(struct sockaddr*)&address,&len);
for(int i = 0;i < msize;i++){
for(int j = 0;j < msize;j++){
printf("%d\t",matrix[i][j]);
}
printf("\n");
}
return 0;
}