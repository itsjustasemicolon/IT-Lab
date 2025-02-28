#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8099
#define BUFFER_SIZE 256

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
   
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    // Set up server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Convert IPv4 address from text to binary (localhost)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        error("Invalid address / Address not supported");
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed");
    }

    // Sending and receiving messages
    while (1) {
        printf("Enter message: ");
        bzero(buffer, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
       
        // Send message to the server
        send(sockfd, buffer, strlen(buffer), 0);
       
        // Read response from the server
        bzero(buffer, BUFFER_SIZE);
        n = read(sockfd, buffer, BUFFER_SIZE);
        if (n > 0) {
            printf("Server: %s", buffer);
        } else {
            break;
        }

        // Exit condition
        if (strncmp("bye", buffer, 3) == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}
