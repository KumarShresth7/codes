#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h> // close

int main()
{
    char message[100];
    struct sockaddr_in serverAddress;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(22000);

    bind(socket_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(socket_fd, 10);  

    int client_fd;

    while (1)
    {
        client_fd = accept(socket_fd,NULL, NULL);
        bzero(message, 100);
        recv(client_fd, message, 100, 0);

        printf("Received at Server -> %s", message);

        send(client_fd, message, strlen(message), 0);

        close(client_fd);
    }
}
