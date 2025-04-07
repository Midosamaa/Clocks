#include <iostream>
#include <sstream>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <arpa/inet.h>

struct ClockMotion {
    float hourAngle;
    float minuteAngle;
};

std::string serializeClockMotion(const ClockMotion& motion) {
    std::ostringstream oss;
    oss << "{"
        << "\"hourAngle\":" << motion.hourAngle << ","
        << "\"minuteAngle\":" << motion.minuteAngle
        << "}";
    return oss.str();
}

std::string getCurrentTimeJson() {
    time_t now = time(nullptr);
    struct tm* localTime = localtime(&now);

    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;

    std::ostringstream oss;
    oss << "{\"time\":\""
        << (hour < 10 ? "0" : "") << hour
        << (minute < 10 ? "0" : "") << minute
        << "\"}";
    return oss.str();
}

bool sendTo(int port, const std::string& payload, const std::string& label) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "[" << label << "] Failed to create socket\n";
        return false;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "[" << label << "] Failed to connect to port " << port << "\n";
        close(sock);
        return false;
    }

    send(sock, payload.c_str(), payload.size(), 0);
    close(sock);

    std::cout << "[" << label << "] Sent: " << payload << std::endl;
    return true;
}

void sendToSimulatorUntilSuccess(const std::string& jsonTime) {
    while (!sendTo(6000, jsonTime, "SIMULATOR")) {
        usleep(500000); // retry every 0.5s
    }
}

void sendToReceptorUntilSuccess(const ClockMotion& motion) {
    std::string payload = serializeClockMotion(motion);
    while (!sendTo(5000, payload, "RECEPTOR")) {
        usleep(500000); // retry every 0.5s
    }
}

int main() {
    std::string previousMinute = "";

    while (true) {
        time_t now = time(nullptr);
        struct tm* localTime = localtime(&now);

        int hour = localTime->tm_hour;
        int minute = localTime->tm_min;

        std::ostringstream timeStream;
        timeStream << (hour < 10 ? "0" : "") << hour
                   << (minute < 10 ? "0" : "") << minute;
        std::string currentMinute = timeStream.str();

        if (currentMinute != previousMinute) {
            // Build message
            std::string timeJson = "{\"time\":\"" + currentMinute + "\"}";

            ClockMotion motion;
            motion.hourAngle = hour * 30 % 360;
            motion.minuteAngle = minute * 6 % 360;

            // Retry both sends until successful
            sendToSimulatorUntilSuccess(timeJson);
            sendToReceptorUntilSuccess(motion);

            previousMinute = currentMinute;
        }

        usleep(500000); // Still check every 0.5s for minute change
    }

    return 0;
}
