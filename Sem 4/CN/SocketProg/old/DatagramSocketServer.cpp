#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    
    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket with server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, 
             sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(cliaddr);
    char buffer[1024];
    
    int n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, 
                    (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    
    sendto(sockfd, "Hello from server", 17, MSG_CONFIRM, 
          (const struct sockaddr *)&cliaddr, len);
    
    close(sockfd);
    return 0;
}
