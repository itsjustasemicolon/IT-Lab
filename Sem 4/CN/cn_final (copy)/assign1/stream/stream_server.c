#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

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

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        perror("bind"), exit(1);

    listen(sockfd, 5); // Allow multiple pending connections
    printf("Server listening on %s:%d\n", serv_ip, port);

    while(1) {
        printf("Waiting for connection...\n");
        int connfd = accept(sockfd, NULL, NULL);
        if (connfd < 0) {
            perror("accept");
            continue;
        }
        printf("Client connected!\n");

        if (fork() == 0) {
            close(sockfd); // Child doesn't need listener

            char buf[MAX_SIZE];
            pid_t pid = fork();
            if (pid == 0) {
                // Child: Send messages to client
                while(1) {
                    printf("Server: ");
                    fflush(stdout);
                    bzero(buf, MAX_SIZE);
                    fgets(buf, MAX_SIZE, stdin);
                    write(connfd, buf, strlen(buf));
                    if (strncmp(buf, "bye", 3) == 0) break;
                }
                exit(0);
            } else {
                // Parent: Receive messages from client
                while(1) {
                    bzero(buf, MAX_SIZE);
                    int n = read(connfd, buf, MAX_SIZE);
                    if (n <= 0) break;
                    printf("\nClient: %s", buf);
                     if (strncmp(buf, "bye", 3) == 0) {
                        write(connfd, "goodbye\n", 8);
                        break;
                    } else {
                        write(connfd, "ok\n", 3);
                    }
                }
                close(connfd);
                exit(0);
            }
        } else {
            close(connfd); // Parent closes connected socket
        }
    }

    close(sockfd);
    return 0;
}


