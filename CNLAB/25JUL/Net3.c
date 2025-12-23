#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>          
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);               
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    memset(&(server_addr.sin_zero), 0, 8);         

    
    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is ready and waiting for messages on port 8080...\n");

 
    client_len = sizeof(client_addr);
    int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &client_addr, &client_len);
    if (n < 0) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';  
    printf(" Client says: %s\n", buffer);

    
    const char *message = "Hello from server";
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *) &client_addr, client_len) < 0) {
        perror("sendto failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Reply sent to client.\n");

  
    close(sockfd);
    printf("Socket closed. Server exiting.\n");

    return 0;
}

