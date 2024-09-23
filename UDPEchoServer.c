#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 22000
#define BUF_SIZE 100

int main()
{

    char buffer[BUF_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);

    // Create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    // Initialize server address structure
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind the socket
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
    printf("UDP Echo Server is running on port %d\n", PORT);

    while (1)
    {
        // Receive message from client
        bzero(buffer, BUF_SIZE);
        recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&cliaddr, &cliaddr_len);
        printf("Received: %s", buffer);

        // Echo back the message to the client
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, cliaddr_len);
    }

    close(sockfd);
    return 0;
}
