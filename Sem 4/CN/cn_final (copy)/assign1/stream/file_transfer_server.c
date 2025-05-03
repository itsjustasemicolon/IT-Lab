#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

void receive_file(FILE *fp, int sockfd) {
    char buffer[MAX_SIZE];
    int n;

    while ((n = recv(sockfd, buffer, MAX_SIZE, 0)) > 0) {
        fwrite(buffer, 1, n, fp);
    }
    if (n < 0) {
        perror("Error receiving file");
        exit(1);
    }
}

int main() {
    int port;
    char serv_ip[INET_ADDRSTRLEN];

    printf("Enter server IP: ");
    scanf("%s", serv_ip);

    printf("Enter port: ");
    scanf("%d", &port);
    getchar(); //

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = inet_addr(serv_ip)
    };

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    listen(sockfd, 1);
    printf("Waiting for connection...\n");

    int connfd = accept(sockfd, NULL, NULL);
    if (connfd < 0) {
        perror("accept");
        close(sockfd);
        exit(1);
    }

    printf("Client connected!\n");

    // Open file to write received data
    FILE *fp = fopen("received.png", "wb");
    if (fp == NULL) {
        perror("File open error");
        close(connfd);
        close(sockfd);
        exit(1);
    }

    receive_file(fp, connfd);

    fclose(fp);
    close(connfd);
    close(sockfd);

    printf("File received successfully.\n");

    return 0;
}
