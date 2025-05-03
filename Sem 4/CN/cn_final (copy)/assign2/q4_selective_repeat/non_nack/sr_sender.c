#include "protocol.h"
#include "crc.h"
#include <time.h>

#define WINDOW_SIZE 4
#define CHUNK_SIZE 8
#define MAX_FRAMES 100
#define MAX_SEQ_NUMBER 7

int seq_counter = 0;

void MakeFrame(Frame *f, char *data, int seq) {
    f->seq = seq;
    f->ack = 0;
    strncpy(f->data, data, strlen(data));
    f->crc = crc_16((unsigned char *)data, strlen(data));
}

void CorruptFrame(Frame *f) {
    int pos = rand() % strlen(f->data);
    f->data[pos] ^= (1 << (rand() % 8));
}

int BuildFrames(char *input, Frame frames[], int *frame_count) {
    int len = strlen(input);
    int idx = 0, pos = 0;
    while (pos < len) {
        Frame f;
        bzero(&f, sizeof(f));
        strncpy(f.data, input + pos, CHUNK_SIZE);
        MakeFrame(&f, f.data, seq_counter);
        frames[idx++] = f;
        seq_counter = (seq_counter + 1) % (MAX_SEQ_NUMBER + 1);
        pos += CHUNK_SIZE;
    }
    *frame_count = idx;
    return 0;
}

int main() {
    srand(time(0));
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) exit(1);

    char ip[INET_ADDRSTRLEN];
    unsigned short port;
    GetAddress(ip);
    GetPort(&port);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = inet_addr(ip)
    };

    int prob;
    printf("Enter corruption probability (%%): ");
    scanf("%d", &prob);
    getchar();

    while (1) {
        char input[1024];
        bzero(input, sizeof(input));
        printf("Enter message: ");
        fgets(input, sizeof(input), stdin);
        if (strlen(input) <= 1) continue;

        Frame frames[MAX_FRAMES];
        int total;
        BuildFrames(input, frames, &total);

        int acked[MAX_FRAMES] = {0};
        int base = 0;

        while (base < total) {
        int i = 0;    
	for (i = 0; i < total; i++) {
                if (!acked[i] && i < base + WINDOW_SIZE) {
                    Frame f = frames[i];
                    if (rand() % 100 < prob) {
                        CorruptFrame(&f);
                        printf("Corrupted frame seq %d\n", f.seq);
                    } else {
                        printf("Sent frame seq %d\n", f.seq);
                    }
                    sendto(sockfd, &f, sizeof(f), 0, (struct sockaddr *)&addr, sizeof(addr));
                }
            }

            SocketTime(sockfd, 2);
            Frame ack;
            struct sockaddr_in from;
            socklen_t len = sizeof(from);
            int r = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&from, &len);

            if (r > 0 && ack.ack) {
                int i = 0;
		for (i = 0; i < total; i++) {
                    if (frames[i].seq == ack.seq) {
                        acked[i] = 1;
                        printf("Received ACK for seq %d\n", ack.seq);
                        break;
                    }
                }
                while (acked[base]) base++;
            } else {
                printf("Timeout, resending window...\n");
            }
        }
    }

    close(sockfd);
    return 0;
}
