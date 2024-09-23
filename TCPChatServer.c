#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define message_SIZE 1024

int main()
{
    struct sockaddr_in servaddr;
    char message[message_SIZE];

    // Create TCP socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind and listen
    bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(socket_fd, 3);

    // Chat loop
    while (1)
    {
        int client_fd = accept(socket_fd, NULL, NULL);
        bzero(message, 100);

        recv(client_fd, message, message_SIZE, 0);
        printf("Client: %s\n", message);

        if (strcmp(message, "exit") == 0)
            break;
            
        send(client_fd, message, strlen(message), 0);
    }

    close(client_fd);
    close(socket_fd);
    return 0;
}
