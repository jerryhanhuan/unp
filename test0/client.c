#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int ret = 0;
    int sockfd = 0;
    char ip[16] = {0};
    int port = 0;
    struct sockaddr_in svraddr;

    if (argc < 3)
    {
        printf("usage ip port\n");
        return -1;
    }
    strcpy(ip, argv[1]);
    port = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket failed");
        return -1;
    }
    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &(svraddr.sin_addr));

    if ((ret = connect(sockfd, (struct sockaddr *)&svraddr, sizeof(svraddr))) < 0)
    {
        perror("connect failed");
        close(sockfd);
        return -1;
    }
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    int len = 0;
    while (1)
    {
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
        printf("input msg::");
        // ret = scanf("%[^\n]",sendbuf);
        NULL == fgets(sendbuf, sizeof(sendbuf), stdin);
        len = send(sockfd, sendbuf, strlen(sendbuf), 0);
        printf("send len[%d]  buf[%s]\n", len, sendbuf);
        len = recv(sockfd, recvbuf, sizeof(recvbuf), 0);
        printf("recv len[%d] buf[%s]\n", len, recvbuf);
        continue;
    }
    close(sockfd);
    return 0;
}
