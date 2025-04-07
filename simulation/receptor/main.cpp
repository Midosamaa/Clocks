#include <iostream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

// Struct to hold angles
struct ClockMotion {
    float hourAngle;
    float minuteAngle;
};

// Simple parser for: {"hourAngle":270,"minuteAngle":90}
ClockMotion parseClockMotion(const std::string& json) {
    ClockMotion motion{};

    size_t hPos = json.find("\"hourAngle\":");
    size_t mPos = json.find("\"minuteAngle\":");

    if (hPos != std::string::npos && mPos != std::string::npos) {
        motion.hourAngle = std::stof(json.substr(hPos + 12, json.find(",", hPos) - (hPos + 12)));
        motion.minuteAngle = std::stof(json.substr(mPos + 14, json.find("}", mPos) - (mPos + 14)));
    }

    return motion;
}

int main() {
    int server_fd;
    sockaddr_in server_addr{}, client_addr{};
    socklen_t client_len = sizeof(client_addr);
    const int PORT = 5000;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "[RECEPTOR] Failed to create socket\n";
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "[RECEPTOR] Bind failed\n";
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        std::cerr << "[RECEPTOR] Listen failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "[RECEPTOR] Listening for clock angles on port " << PORT << "...\n";

    while (true) {
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "[RECEPTOR] Accept failed\n";
            continue;
        }

        std::cout << "[RECEPTOR] Connected to sender.\n";

        // Now loop and wait for multiple messages on the same connection
        while (true) {
            char buffer[1024] = {0};
            int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);

            if (bytesRead <= 0) {
                std::cout << "[RECEPTOR] Client disconnected.\n";
                break; // Exit inner loop and wait for new client
            }

            buffer[bytesRead] = '\0';
            std::string received(buffer);
            ClockMotion motion = parseClockMotion(received);

            std::cout << "[RECEPTOR] Received angles:\n";
            std::cout << "  Hour Angle: " << motion.hourAngle << "\n";
            std::cout << "  Minute Angle: " << motion.minuteAngle << "\n";
        }

        close(client_fd); // Close connection when client disconnects
    }

    close(server_fd);
    return 0;
}
