#include "communication.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>

// Converts ClockMotion to a JSON-like string
string serializeClockMotion(const ClockMotion& motion) {
    ostringstream oss;
    oss << "{"
        << "\"hourAngle\":" << motion.hourAngle << ","
        << "\"minuteAngle\":" << motion.minuteAngle << ","
        << "\"speed\":" << motion.speed
        << "}";
    return oss.str();
}

void sendClockMotionToSupervisor(const ClockMotion& motion) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "[COMM] Failed to create socket\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "[COMM] Failed to connect to supervisor\n";
        close(sock);
        return;
    }

    string payload = serializeClockMotion(motion);
    send(sock, payload.c_str(), payload.size(), 0);
    close(sock);

    cout << "[COMM] Sent to supervisor: " << payload << endl;
}
