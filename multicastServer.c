#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MULTICAST_GROUP "239.0.0.1" // Multicast group address
#define MULTICAST_PORT 12345        // Multicast port
#define BUFFER_SIZE 256

int main() {
    int sockfd;
    struct sockaddr_in local_addr;
    struct ip_mreq multicast_request;
    char buffer[BUFFER_SIZE];

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Allow multiple processes to use the same port
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("Setting SO_REUSEADDR failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a local address and port
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to all local interfaces
    local_addr.sin_port = htons(MULTICAST_PORT);

    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) {
        perror("Binding failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Join the multicast group
    multicast_request.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
    multicast_request.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast_request, sizeof(multicast_request)) < 0) {
        perror("Joining multicast group failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for multicast messages...\n");

    // Receive messages
    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, NULL, NULL);
        if (n < 0) {
            perror("Receiving message failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0'; // Null-terminate the received data
        printf("Received: %s\n", buffer);
    }

    // Leave the multicast group
    if (setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &multicast_request, sizeof(multicast_request)) < 0) {
        perror("Dropping multicast group failed");
    }

    // Close the socket
    close(sockfd);
    return 0;
}
