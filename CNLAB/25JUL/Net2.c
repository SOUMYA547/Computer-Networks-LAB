#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>  

#define BUF_SIZE 1024

int main() {
    int sockfd;  
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr, cliaddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0, 8);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    len = sizeof(cliaddr);
    int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("Client Says: %s\n", buffer);

    const char *reply = "Hello From Server";
    sendto(sockfd, reply, strlen(reply), 0, (struct sockaddr *)&cliaddr, len); 

    printf("Socket Binding and communication successfully completed\n");

    close(sockfd);
    return 0;
}

