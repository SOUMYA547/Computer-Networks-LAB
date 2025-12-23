#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Sender IP> <Sender Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *sender_ip = argv[1];
    int sender_port = atoi(argv[2]);

    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(sender_port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    struct sockaddr_in replyaddr;
    memset(&replyaddr, 0, sizeof(replyaddr));
    replyaddr.sin_family = AF_INET;
    replyaddr.sin_port = htons(sender_port + 1); // different port for sending reply
    replyaddr.sin_addr.s_addr = inet_addr(sender_ip);

    socklen_t len = sizeof(cliaddr);

    while (1) {
        int n = recvfrom(sockfd, buffer, MAXLINE, 0,
                         (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Sender: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;

        printf("You: ");
        fgets(buffer, MAXLINE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        sendto(sockfd, buffer, strlen(buffer), 0,
               (const struct sockaddr *)&replyaddr, sizeof(replyaddr));

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sockfd);
    return 0;
}

