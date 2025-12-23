#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081          // Must match server
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(servaddr);

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        printf("Enter lowercase string (or 'exit' to quit): ");
        fgets(buffer, BUF_SIZE, stdin);

        // Send message
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&servaddr, len);

        if (strncmp(buffer, "exit", 4) == 0)
            break;

        // Receive reply
        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server Uppercase: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

