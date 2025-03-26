#include <iostream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

int main() {
    int server_fd;
    sockaddr_in server_addr{}, client_addr{};
    socklen_t client_len = sizeof(client_addr);
    const int PORT = 5000;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    // Bind
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed\n";
        close(server_fd);
        return 1;
    }

    // Listen
    if (listen(server_fd, 1) < 0) {
        std::cerr << "Listen failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "[SUPERVISOR] Server listening on port " << PORT << "...\n";

    while (true) {
        // Accept a new connection
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "[SUPERVISOR] Accept failed\n";
            continue;
        }

        // Receive data
        char buffer[1024] = {0};
        int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::cout << "[SUPERVISOR] Received: " << buffer << "\n";
        } else {
            std::cerr << "[SUPERVISOR] No data received or error occurred\n";
        }

        close(client_fd);  // Close current client, then wait for next
    }

    // Should never reach here
    close(server_fd);
    return 0;
}
