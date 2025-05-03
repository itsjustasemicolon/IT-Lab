#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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

    pid_t pid = fork();
    if (pid == 0) {
        // Child: Send messages
        char msg[MAX_SIZE];
        while(1) {
            printf("You: ");
            fflush(stdout);
            bzero(msg, MAX_SIZE);
            fgets(msg, MAX_SIZE, stdin);
            write(sockfd, msg, strlen(msg));
            if (strncmp(msg, "bye", 3) == 0) break;
        }
        exit(0);
    } else {
        // Parent: Receive messages
        char buf[MAX_SIZE];
        while(1) {
            bzero(buf, MAX_SIZE);
            int n = read(sockfd, buf, MAX_SIZE);
            if (n <= 0) break;
            printf("\nServer: %s", buf);
            if (strncmp(buf, "goodbye", 7) == 0) break;
        }
        close(sockfd);
        printf("Disconnected.\n");
    }

    return 0;
}


