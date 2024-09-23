#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

// #define  err_log(log) do{perror(log); exit(1);}while(0)
#define  N 128

int main(int argc, const char *argv[])
{
    char message[N];
    struct sockaddr_in broadcastaddr;
    
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&broadcastaddr, sizeof(broadcastaddr));

    broadcastaddr.sin_family = AF_INET;
    broadcastaddr.sin_addr.s_addr = INADDR_ANY;   
    broadcastaddr.sin_port = htons(10000);

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int));
    
    while(1)
    {
        printf("Input > ");
        fgets(message, N, stdin);
        sendto(sockfd,message, N, 0, (struct sockaddr *)&broadcastaddr, sizeof(broadcastaddr));
    }
    
    return 0;
}
