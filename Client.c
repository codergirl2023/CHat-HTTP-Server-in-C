#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char const* argv[]){
    if (argc != 3) {
        printf("Usage: %s <ip-address> <port>\n", argv[0]);
        return -1;
    }
    const char* ipAddress = argv[1];
    int port = atoi(argv[2]);

    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in serverAddress;
    struct sockaddr* addr = (struct sockaddr*)&serverAddress;
    socklen_t addrlen = sizeof(serverAddress);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ipAddress, &(serverAddress.sin_addr)) <= 0) {
        perror("Invalid address/Address not supported");
        return -1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error while creating socket.");
        _exit(1);
    }

    int status = connect(sockfd, addr, addrlen);
    if (status < 0) {
        perror("Couldn't connect with the server");
        _exit(1);
    }

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // Take input from the console to send to the server
        fgets(buffer, sizeof(buffer), stdin);
        
        // Send the message to the server
        int bytesWritten = write(sockfd, buffer, strlen(buffer));
        if (bytesWritten < 0) {
            perror("Error while writing to socket.");
            _exit(1);
        }
        // Break the loop if "bye" is received from the server
        if (strcmp(buffer, "bye\n") == 0)
                break;
        memset(buffer, 0, sizeof(buffer));

        int bytesRead = read(sockfd, buffer, sizeof(buffer));
        if (bytesRead < 0) {
            perror("Error while reading from socket.");
            _exit(1);
        }
        printf("Server: %s", buffer);
        
       
    }

    close(sockfd);
    return 0;
}
