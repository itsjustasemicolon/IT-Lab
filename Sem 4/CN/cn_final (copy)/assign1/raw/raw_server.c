#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <fcntl.h>

#define MAX_SIZE 4096

// Function to print IP header details
void print_ip_header(struct iphdr *iph) {
    printf("IP Header:\n");
    printf("   |-IP Version      : %d\n", iph->version);
    printf("   |-IP Header Length: %d\n", iph->ihl);
    printf("   |-Type of Service : %d\n", iph->tos);
    printf("   |-Total Length    : %d\n", ntohs(iph->tot_len));
    printf("   |-Identification  : %d\n", ntohs(iph->id));
    printf("   |-Time to Live    : %d\n", iph->ttl);
    printf("   |-Protocol        : %d\n", iph->protocol);
    printf("   |-Source IP       : %s\n", inet_ntoa(*(struct in_addr *)&iph->saddr));
    printf("   |-Destination IP  : %s\n", inet_ntoa(*(struct in_addr *)&iph->daddr));
}

// Function to print ICMP header details
void print_icmp_header(struct icmphdr *icmph) {
    printf("ICMP Header:\n");
    printf("   |-Type : %d\n", icmph->type);
    printf("   |-Code : %d\n", icmph->code);
    printf("   |-Checksum : %d\n", icmph->checksum);
    printf("   |-ID : %d\n", ntohs(icmph->un.echo.id));
    printf("   |-Sequence : %d\n", ntohs(icmph->un.echo.sequence));
}

int main() {
    int sock;
    struct sockaddr_in addr;
    char buffer[MAX_SIZE];  // Buffer to store received raw packet
    socklen_t addr_len = sizeof(addr);
    fd_set readfds;
    char ip_add[INET_ADDRSTRLEN];
    unsigned short port;
    // Create a raw socket
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }
	
    printf("Enter IP address: ");
    scanf("%s", ip_add);

    printf("Enter port number: ");
    scanf("%hu", &port);

    fcntl(sock, F_SETFL, O_NONBLOCK);  // Set socket to non-blocking

    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip_add);

    printf("Server is ready to receive messages...\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);

        if (select(sock + 1, &readfds, NULL, NULL, NULL) > 0) {
            if (FD_ISSET(sock, &readfds)) {
                memset(buffer, 0, sizeof(buffer));
                int len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addr_len);
                if (len > 0) {
                    // Extract IP header and ICMP header from the received packet
                    struct iphdr *iph = (struct iphdr *)buffer;
                    print_ip_header(iph);

                    struct icmphdr *icmph = (struct icmphdr *)(buffer + sizeof(struct iphdr));
                    print_icmp_header(icmph);

                    // Extract and print the payload
                    // The payload starts after the IP and ICMP headers
                    // Extract and print the payload
			// The payload starts after the IP and ICMP headers
		int payload_offset = sizeof(struct iphdr) + sizeof(struct icmphdr);
		int payload_size = len - payload_offset;  // Remaining size is the payload

		// Ensure we don't treat the whole buffer as a string
		printf("Payload Data: ");
		int i;
		for (i = 0; i < payload_size; i++) {
		    printf("%c", buffer[payload_offset + i + 20]);
		}
		printf("\n");                    
                }
            }
        } else {
            printf("Waiting...\n");
        }
    }

    close(sock);
    return 0;
}

