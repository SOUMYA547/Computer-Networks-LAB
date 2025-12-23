#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>             
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    char buffer[BUF_SIZE];
    const char *message = "Hello from client";

   
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); 
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(server_addr.sin_zero), 0, 8);

    
    addr_len = sizeof(server_addr);
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, addr_len) < 0) {
        perror("sendto failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf(" Sent to server: %s\n", message);

    int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0'; 
    printf("Server replied: %s\n", buffer);

   
    close(sockfd);
    printf("Socket closed. Client exiting.\n");

    return 0;
}

