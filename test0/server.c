#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


/*
    ipv4
    create socket and bind server address and ip

*/

int sock_bind(char *ip,int port)
{
    
    int sockfd = 0;
    int ret = 0;
    struct sockaddr_in svraddr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        perror("socket failed");
        return -1;
    }
    memset(&svraddr,0,sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(port);
    if(ip)
        inet_pton(AF_INET,ip,&(svraddr.sin_addr));
    else
        svraddr.sin_addr = htonl(INADDR_ANY);

    if((ret = bind(sockfd,(struct sockaddr *)&svraddr,sizeof(svraddr)))<0)
    {
        perror("bind failed");
        close(sockfd);
        return -2;
    }
    return sockfd;
}


int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("usage port\n");
        return -1;
    }
    int port = atoi(argv[1]);
    int sockfd = sock_bind(NULL,port);
    if(sockfd < 0)
        return -1;
    char recv_buf[1024]={0};
    char send_buf[1024]={0};
    int ret = 0;
    int len = 0;
    while(1)
    {
       memset(recv_buf,0,sizeof(recv_buf));
       memset(send_buf,0,sizeof(send_buf));
       printf("wait for recv data\n"); 
       len = recv(sockfd,recv_buf,sizeof(recv_buf),0);
       if(len<0)
       {
           perror("recv failed");
           continue;
       }
       printf("recv len[%d] buf[%s]\n",len,recv_buf);
       memcpy(send_buf,"Hello,this is the server\n");
       len = send(sockfd,send_buf,strlen(send_buf),0);
    }
    close(sockfd);
    return 0;
}
















