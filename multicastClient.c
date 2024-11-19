#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MULTICAST_GROUP "239.0.0.1" // Multicast group address
#define MULTICAST_PORT 12345        // Multicast port
#define MESSAGE "Hello, Multicast Group!"

int main() {
    int sockfd;
    struct sockaddr_in multicast_addr;
    struct in_addr local_interface;
    int loop = 1;

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the IP_MULTICAST_LOOP option
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
        perror("Setting IP_MULTICAST_LOOP failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Specify the local interface for multicast
    local_interface.s_addr = inet_addr("127.0.0.1"); // Change to your local interface IP
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &local_interface, sizeof(local_interface)) < 0) {
        perror("Setting IP_MULTICAST_IF failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Initialize the multicast address structure
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
    multicast_addr.sin_port = htons(MULTICAST_PORT);

    // Send the multicast message
    if (sendto(sockfd, MESSAGE, strlen(MESSAGE), 0, 
               (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0) {
        perror("Sending message failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", MESSAGE);

    // Close the socket
    close(sockfd);
    return 0;
}
