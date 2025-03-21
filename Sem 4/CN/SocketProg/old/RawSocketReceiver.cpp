#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

int main() {
    int sockfd;
    char buffer[4096];
    
    // Create raw socket
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    while(true) {
        int data_size = recv(sockfd, buffer, 4096, 0);
        if(data_size < 0) {
            perror("recv error");
            exit(EXIT_FAILURE);
        }
        
        struct iphdr *ip = (struct iphdr *)buffer;
        std::cout << "Received packet from: " << inet_ntoa(*(in_addr*)&ip->saddr) 
                  << std::endl;
    }
    
    close(sockfd);
    return 0;
}
