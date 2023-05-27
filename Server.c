#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return -1;
    }

    int port = atoi(argv[1]);

    struct sockaddr_in serverAddress;
    struct sockaddr* addr = (struct sockaddr*)&serverAddress;
    socklen_t addrlen = sizeof(serverAddress);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error while opening socket.");
        _exit(1);
    }

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, addr, addrlen) < 0) {
        perror("Error while binding socket.");
        _exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror("Error while listening socket.");
        _exit(1);
    }

    char buffer[MAX_BUFFER_SIZE];

    int clientSocket = accept(sockfd, (struct sockaddr*)&serverAddress, &addrlen);
    if (clientSocket < 0) {
        perror("Error while creating new socket.");
        _exit(1);
    }
    
    while (1) {
            memset(buffer, 0, sizeof(buffer));
            
            int bytesRead = read(clientSocket, buffer, sizeof(buffer));
            if (bytesRead < 0) {
                perror("Error while reading from socket.");
                _exit(1);
            }
            
            printf("Client: %s", buffer);

            if (strcmp(buffer, "bye\n") == 0)
                break;
            
            memset(buffer, 0, sizeof(buffer));
            // Take input from the console to send to the client
            fgets(buffer, sizeof(buffer), stdin);
            // Send the message to the client
            int bytesWritten = write(clientSocket, buffer, strlen(buffer));
            if (bytesWritten < 0) {
                perror("Error while writing to socket.");
                exit(1);
            }
        }

        close(clientSocket);
    

    close(sockfd);

    return 0;
}
