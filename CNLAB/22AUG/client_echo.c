#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(servaddr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        printf("Enter message (or 'exit' to quit): ");
        fgets(buffer, BUF_SIZE, stdin);

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&servaddr, len);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server Echo: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

