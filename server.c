// Server side C program to demonstrate Socket Programming
// Compile: gcc server.c -o server
// Run:     ./server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Step 1: Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Allow the port to be reused immediately after the server stops
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Step 2: Bind the socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n", PORT);

    // Step 4: Accept a connection from a client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Step 5: Read message from client
    read(new_socket, buffer, sizeof(buffer) - 1);
    printf("Message from client: %s\n", buffer);

    // Step 6: Send reply to client
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent to client\n");

    // Step 7: Close the sockets
    close(new_socket);
    close(server_fd);
    return 0;
}
