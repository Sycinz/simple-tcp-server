#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Initializing socket and error handling
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket initializing error");
        return 1;
    } else {
        printf("Socket ready to work!\n");
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(2222);

    // Checking if socket binding was successful
    if (bind(sock,
        (struct sockaddr*)&server_address,
        sizeof(server_address)) < 0) {
            perror("bind");
            close(sock);
            return 1;
        }

    // Listening with error handling
    if (listen(sock, 5) < 0) {
            perror("listen");
            close(sock);
            return 1;
        }
    
    printf("Server socket bound and listening on port %d...\n", htons(server_address.sin_port));

    while (1) {
        sleep(1);
    }
    
    // Closing socket
    close(sock);
    return 0;
}
