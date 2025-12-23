// sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Receiver IP> <Receiver Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *receiver_ip = argv[1];
    int receiver_port = atoi(argv[2]);

    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(receiver_port);
    servaddr.sin_addr.s_addr = inet_addr(receiver_ip);

    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(receiver_port + 1); // different port for reply

    bind(sockfd, (const struct sockaddr *)&myaddr, sizeof(myaddr));

    socklen_t len = sizeof(servaddr);

    while (1) {
        printf("You: ");
        fgets(buffer, MAXLINE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // remove newline

        sendto(sockfd, buffer, strlen(buffer), 0,
               (const struct sockaddr *)&servaddr, len);

        if (strcmp(buffer, "exit") == 0)
            break;

        int n = recvfrom(sockfd, buffer, MAXLINE, 0,
                         (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Receiver: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sockfd);
    return 0;
}
