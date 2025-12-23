#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define OLD_PORT 8080     
#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUF_SIZE];
    socklen_t len = sizeof(servaddr);

    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(OLD_PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    strcpy(buffer, "Hello, are you there?");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&servaddr, len);

    printf("Client sent message to old port %d.\n", OLD_PORT);
    printf("But server is on a different port → so message is lost.\n");

    close(sockfd);
    return 0;
}

