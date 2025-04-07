#include "communication.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>

// Converts ClockMotion to a JSON-like string
std::string serializeClockMotion(const ClockMotion& motion) {
    std::ostringstream oss;
    oss << "{"
        << "\"hourAngle\":" << motion.hourAngle << ","
        << "\"minuteAngle\":" << motion.minuteAngle
        << "}";
    return oss.str();
}

// Sends the motion data to the receptor (not supervisor!)
void sendClockMotionToReceptor(const ClockMotion& motion) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "[COMM] Failed to create socket\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "[COMM] Failed to connect to receptor\n";
        close(sock);
        return;
    }

    std::string payload = serializeClockMotion(motion);
    send(sock, payload.c_str(), payload.size(), 0);
    close(sock);

    std::cout << "[COMM] Sent to receptor: " << payload << std::endl;
}
