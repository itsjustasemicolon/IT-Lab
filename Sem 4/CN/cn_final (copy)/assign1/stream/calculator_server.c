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

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        perror("bind"), exit(1);

    listen(sockfd, 5);
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
            close(sockfd);
            char buf[MAX_SIZE];
            
            while(1) {
                bzero(buf, MAX_SIZE);
                int n = read(connfd, buf, MAX_SIZE);
                if (n <= 0) break;
                
                if (strncmp(buf, "bye", 3) == 0) {
                    write(connfd, "goodbye\n", 8);
                    break;
                }

                double num1, num2, result;
                char op;
                if (sscanf(buf, "%lf %c %lf", &num1, &op, &num2) != 3) {
                    write(connfd, "Error: Invalid format. Use: num op num\n", 38);
                    continue;
                }

                int error = 0;
                switch(op) {
                    case '+': result = num1 + num2; break;
                    case '-': result = num1 - num2; break;
                    case '*': result = num1 * num2; break;
                    case '/': 
                        if (num2 == 0) {
                            write(connfd, "Error: Division by zero\n", 24);
                            error = 1;
                        } else {
                            result = num1 / num2;
                        }
                        break;
                    default:
                        write(connfd, "Error: Invalid operator (+, -, *, /)\n", 37);
                        error = 1;
                }

                if (!error) {
                    char response[MAX_SIZE];
                    snprintf(response, MAX_SIZE, "Result: %.2lf\n", result);
                    write(connfd, response, strlen(response));
                }
            }
            close(connfd);
            exit(0);
        } else {
            close(connfd);
        }
    }
    close(sockfd);
    return 0;
}
