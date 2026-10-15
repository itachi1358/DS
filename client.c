// Client side C program to demonstrate Socket Programming
// Compile: gcc client.c -o client
// Run:     ./client   (start the server first)

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    // Step 1: Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address / Address not supported\n");
        return -1;
    }

    // Step 2: Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    // Step 3: Send message to server
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent to server\n");

    // Step 4: Read reply from server
    read(sock, buffer, sizeof(buffer) - 1);
    printf("Message from server: %s\n", buffer);

    // Step 5: Close the socket
    close(sock);
    return 0;
}
