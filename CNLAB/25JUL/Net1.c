#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 5000
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE] = "Hello from client";
    char recvbuf[BUFFER_SIZE];
    socklen_t addr_len = sizeof(servaddr);

  
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to your server IP

    
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, addr_len);

    
    int n = recvfrom(sockfd, recvbuf, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &addr_len);
    if (n < 0) {
        perror("Error in receiving data");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    recvbuf[n] = '\0';
    printf("Server : %s\n", recvbuf);

    close(sockfd);
    return 0;
}

