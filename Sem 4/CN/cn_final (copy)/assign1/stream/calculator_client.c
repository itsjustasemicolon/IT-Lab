#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

int main() {
    int port;
    char serv_ip[INET_ADDRSTRLEN];
    
    printf("Enter server IP: ");
    scanf("%s", serv_ip);
    printf("Enter port: ");
    scanf("%d", &port);
    getchar();

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("socket"), exit(1);

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = inet_addr(serv_ip)
    };

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        perror("connect"), exit(1);

    printf("Connected to server!\n");
    char msg[MAX_SIZE];
    
    while(1) {
        printf("Enter calculation (num op num) or 'bye': ");
        fgets(msg, MAX_SIZE, stdin);
        msg[strcspn(msg, "\n")] = 0; // Remove newline
        
        write(sockfd, msg, strlen(msg));
        
        if (strcmp(msg, "bye") == 0) break;

        char buf[MAX_SIZE];
        bzero(buf, MAX_SIZE);
        read(sockfd, buf, MAX_SIZE);
        printf("Server: %s", buf);
    }
    
    close(sockfd);
    printf("Disconnected.\n");
    return 0;
}
