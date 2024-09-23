    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <arpa/inet.h>

    #define PORT 8080
    #define message_SIZE 1024

    int main()
    {
        struct sockaddr_in serv_addr;
        char message[message_SIZE];

        // Create TCP sock_fdet
        int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        // Connect to server
        connect(sock_fd, (struct sock_fd_addr *)&serv_addr, sizeof(serv_addr));

        // Chat loop
        while (1)
        {
            printf("You: ");
            fgets(message, message_SIZE, stdin);

            send(sock_fd, message, strlen(message), 0);

            if (strcmp(message, "exit") == 0)
                break;
                
            recv(sock_fd, message, message_SIZE, 0);
            printf("Server: %s\n", message);
        }

        close(sock_fd);
        return 0;
    }
