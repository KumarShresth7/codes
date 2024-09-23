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
    char sendline[BUF_SIZE];
    char recvline[BUF_SIZE];
    struct sockaddr_in servaddr;

    // Create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    while (1)
    {
        bzero(sendline, BUF_SIZE);
        bzero(recvline, BUF_SIZE);

        // Read input from user
        printf("Enter message: ");
        fgets(sendline, BUF_SIZE, stdin);

        // Send message to server
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        // Receive echo from server
        recvfrom(sockfd, recvline, BUF_SIZE, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("Echo from server: %s", recvline);
    }

    close(sockfd);
    return 0;
}
