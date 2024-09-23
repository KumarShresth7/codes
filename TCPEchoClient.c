#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in serverAddress;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(22000);
    
    connect(socket_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    while (1)
    {
        bzero(sendline, 100);
        bzero(recvline, 100);
        fgets(sendline, 100, stdin);

        printf("Sent by Client -> %s", sendline);

        send(socket_fd, sendline, strlen(sendline), 0);
        recv(socket_fd, recvline, 100, 0);

        printf("Received by Client -> %s", recvline);
    }
}
