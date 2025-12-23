#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    socklen_t addrlen = sizeof(address);
    ssize_t n;

    // Create TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare server address
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;         // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(PORT);

    // Bind to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening (backlog of 5 connections)
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("TCP server listening on port %d...\n", PORT);

    // Accept a client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    n = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
    if (n < 0) {
        perror("recv error");
        close(new_socket);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0'; // Null terminate
    printf("Client message: %s\n", buffer);

    // Close sockets
    close(new_socket);
    close(server_fd);

    return 0;
}


