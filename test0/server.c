#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*
    ipv4
    create socket and bind server address and ip

*/

int sock_bind(char *ip, int port)
{

    int sockfd = 0;
    int ret = 0;
    struct sockaddr_in svraddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket failed");
        return -1;
    }
    memset(&svraddr, 0, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(port);
    if (ip)
        inet_pton(AF_INET, ip, &(svraddr.sin_addr));
    else
        svraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((ret = bind(sockfd, (struct sockaddr *)&svraddr, sizeof(svraddr))) < 0)
    {
        perror("bind failed");
        close(sockfd);
        return -2;
    }
    return sockfd;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage port\n");
        return -1;
    }
    int port = atoi(argv[1]);
    int sockfd = sock_bind(NULL, port);
    if (sockfd < 0)
        return -1;

    //listen
    listen(sockfd, 20);

    int accept_fd = 0;
    char recv_buf[1024] = {0};
    char send_buf[1024] = {0};
    int ret = 0;
    int len = 0;
    struct sockaddr_in cliaddr;
    char cli_ip[16] = {0};
    int cli_port = 0;
    socklen_t rlen = sizeof(cliaddr);

    while (1)
    {
        printf("wait for connection......\n");
        if ((accept_fd = accept(sockfd, (struct sockaddr *)&cliaddr, &rlen)) < 0)
        {
            perror("accept failed");
            continue;
        }
        inet_ntop(AF_INET, &cliaddr.sin_addr, cli_ip, sizeof(cli_ip));
        cli_port = ntohs(cliaddr.sin_port);
        printf("accept ok client ip[%s] port[%d]\n", cli_ip, cli_port);
        while (1)
        {
            memset(recv_buf, 0, sizeof(recv_buf));
            memset(send_buf, 0, sizeof(send_buf));
            printf("wait for recv data\n");
            len = recv(accept_fd, recv_buf, sizeof(recv_buf), 0);
            if (len < 0)
            {
                perror("recv failed");
                close(accept_fd);
                break;
            }
            printf("recv len[%d] buf[%s]\n", len, recv_buf);
            printf("input msg::");
            ret = scanf("%s", send_buf);
            len = send(accept_fd, send_buf, strlen(send_buf), 0);
            if (len < 0)
            {
                perror("send failed");
                close(accept_fd);
                break;
            }
            printf("send len[%d] buf[%s]\n", len, send_buf);
        }
        close(accept_fd);
    }
    close(sockfd);
    return 0;
}
