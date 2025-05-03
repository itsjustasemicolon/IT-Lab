#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

void send_file(FILE *fp, int sockfd) {
    char buffer[MAX_SIZE];
    int n;

    while ((n = fread(buffer, 1, MAX_SIZE, fp)) > 0) {
        if (send(sockfd, buffer, n, 0) == -1) {
            perror("Error sending file");
            exit(1);
        }
    }
}

int main() {
    int port;
    char serv_ip[INET_ADDRSTRLEN];

    printf("Enter server IP: ");
    scanf("%s", serv_ip);

    printf("Enter port: ");
    scanf("%d", &port);
    getchar(); 

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

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    printf("Connected to server!\n");

    // Open the file to send
    FILE *fp = fopen("send.png", "rb");
    if (fp == NULL) {
        perror("File open error");
        close(sockfd);
        exit(1);
    }

    send_file(fp, sockfd);

    fclose(fp);
    close(sockfd);
    printf("File sent successfully.\n");

    return 0;
}
