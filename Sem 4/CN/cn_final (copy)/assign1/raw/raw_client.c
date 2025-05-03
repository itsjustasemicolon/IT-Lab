#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#define MAX_SIZE 4096

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;
    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }
    if (len == 1) {
        sum += *(unsigned char *)buf;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main() {
    int sock;
    struct sockaddr_in dest;
    struct iphdr *iph;
    struct icmphdr *icmph;
    char packet[MAX_SIZE];
    char send_msg[1024];
    char ip_addr[INET_ADDRSTRLEN];
    unsigned short port;

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    printf("Enter destination IP address: ");
    scanf("%15s", ip_addr);

    printf("Enter destination port number: ");
    scanf("%hu", &port);

    getchar();

    char src_ip[INET_ADDRSTRLEN];
    printf("Enter source IP address: ");
    scanf("%15s", src_ip);
    getchar();

    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    if (inet_pton(AF_INET, ip_addr, &dest.sin_addr) != 1) {
        fprintf(stderr, "Invalid destination IP address\n");
        exit(1);
    }

    while (1) {
        printf("You: ");
        if (!fgets(send_msg, sizeof(send_msg), stdin)) break;
        send_msg[strcspn(send_msg, "\n")] = 0;

        memset(packet, 0, MAX_SIZE);

        iph = (struct iphdr *)packet;
        iph->ihl = 5;
        iph->version = 4;
        iph->tos = 0;
        iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct icmphdr) + strlen(send_msg));
        iph->id = htons(54321);
        iph->frag_off = 0;
        iph->ttl = 255;
        iph->protocol = IPPROTO_ICMP;
        iph->check = 0;
        if (inet_pton(AF_INET, src_ip, &iph->saddr) != 1) {
            fprintf(stderr, "Invalid source IP address\n");
            exit(1);
        }
        iph->daddr = dest.sin_addr.s_addr;
        iph->check = checksum((unsigned short *)iph, sizeof(struct iphdr));

        icmph = (struct icmphdr *)(packet + sizeof(struct iphdr));
        icmph->type = ICMP_ECHO;
        icmph->code = 0;
        icmph->checksum = 0;
        icmph->un.echo.id = htons(getpid() & 0xFFFF);
        icmph->un.echo.sequence = htons(1);

        memcpy(packet + sizeof(struct iphdr) + sizeof(struct icmphdr), send_msg, strlen(send_msg));

        int icmp_len = sizeof(struct icmphdr) + strlen(send_msg);
        icmph->checksum = checksum((unsigned short *)icmph, icmp_len);

        ssize_t sent_bytes = sendto(sock, packet, sizeof(struct iphdr) + icmp_len, 0, (struct sockaddr *)&dest, sizeof(dest));

        if (sent_bytes < 0) {
            perror("Failed to send packet");
        } else {
            printf("Successfully sent %zd bytes\n", sent_bytes);
        }
    }

    close(sock);
    return 0;
}

