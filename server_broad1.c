#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define N 128
// #define err_log(log) do { perror(log); exit(1); } while(0)

int main()
{
    char message[N];
    struct sockaddr_in broadcastaddr, cli_addr;
    socklen_t addrlen = sizeof(struct sockaddr);

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&broadcastaddr, sizeof(broadcastaddr));

    broadcastaddr.sin_family = AF_INET;
    broadcastaddr.sin_addr.s_addr = INADDR_ANY;   
    broadcastaddr.sin_port = htons(10000);

    bind(socket_fd, (struct sockaddr *)&broadcastaddr, sizeof(broadcastaddr));

    while (1)
    {
        bzero(message, N);
        recvfrom(socket_fd, message, N, 0, (struct sockaddr *)&cli_addr, &addrlen) 
        printf("Received: %s ---> From: %s:%d\n", message, inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    }

    close(socket_fd);
    return 0;
}
