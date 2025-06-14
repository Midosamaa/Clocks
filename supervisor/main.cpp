#include "type_transitions/type_transitions.h"

// Display help instructions
void printHelp() {
    std::cout << "Usage: ./clock_project <direction (1-4)> <transitionType> <transitionDetail>\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  <direction>: Specifies the transition direction\n";
    std::cout << "    - 1 : Right to Left\n";
    std::cout << "    - 2 : Left to Right\n";
    std::cout << "    - 3 : Bottom to Top\n";
    std::cout << "    - 4 : Top to Bottom\n\n";
    std::cout << "    - 5 : All at once (But limited to 4 letters)\n\n";

    std::cout << "  <transitionType>: Effect type applied during minute change\n";
    std::cout << "    - 'pacman'  : Pac-Man animation eating the old time (transitionDetail = NULL)\n";
    std::cout << "    - 'wave'    : Wave animation (transitionDetail = number of waves)\n";
    std::cout << "    - 'stars'   : Star animation (transitionDetail = number of stars)\n";
    std::cout << "    - 'words'   : Temporary word display before showing time (transitionDetail = word to display). If you are using the 5th direction, you will be limited to 4 letters per word. Make sure to write all in capital.\n\n";

    std::cout << "Examples:\n";
    std::cout << "  ./clock_display 1 pacman NULL       # Pac-Man transition right to left\n";
    std::cout << "  ./clock_display 2 wave 5            # Wave effect with 5 waves left to right\n";
    std::cout << "  ./clock_display 3 stars 10          # Display 10 stars from bottom to top\n";
    std::cout << "  ./clock_display 1 words HELLO       # Show 'HELLO' before displaying time\n";
    std::cout << "  ./clock_display 5 words YOYO       # Show 'YOYO' after displaying time at once\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Not enough arguments.\nUse -help for more information.\n";
        return 1;
    }

    std::string firstArg = argv[1];
    if (firstArg == "-help") {
        printHelp();
        return 0;
    }

    if (argc < 4) {
        std::cerr << "Invalid usage! Use -help to see available options.\n";
        return 1;
    }

    // Parse arguments
    int direction = std::stoi(argv[1]);
    std::string transitionType = argv[2];
    std::string transitionDetail = argv[3];

    // Create the 3×8 grid of clocks
    std::vector<std::vector<Clock>> clocks(3, std::vector<Clock>(8, Clock(0, 0))); 
    float startX = 80, startY = 80;
    float spacingX = 120, spacingY = 120;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 8; col++) {
            clocks[row][col] = Clock(startX + col * spacingX, startY + row * spacingY);
        }
    }

    // Get current time
    time_t now = time(0);
    struct tm* localTime = localtime(&now);
    int currentHour = localTime->tm_hour;
    int currentMinute = localTime->tm_min;

    std::string startText = (currentHour < 10 ? "0" : "") + std::to_string(currentHour) +
                            (currentMinute < 10 ? "0" : "") + std::to_string(currentMinute);
    auto startAngles = getTextAngles(startText);

    // Set clocks to neutral angles instantly (no animation)
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 8; col++) {
            clocks[row][col].setInstant(270, 270);
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Animate to the current time (clock hands move to position)
    // float globalMaxDiff = 0.0f;
    // for (int row = 0; row < 3; ++row) {
    //     for (int col = 0; col < 8; ++col) {
    //     if (col < static_cast<int>(startAngles.size()) && row < static_cast<int>(startAngles[col].size())){
    //             float diffH = angularDistance(270.0f, startAngles[col][row].first);
    //             float diffM = angularDistance(270.0f, startAngles[col][row].second);
    //             globalMaxDiff = std::max(globalMaxDiff, std::max(diffH, diffM));
    //         }
    //     }
    // }

    // int steps = std::max(1, static_cast<int>(globalMaxDiff * MAXSTEP));
    // const int delayMs = 5;

    // for (int s = 0; s <= steps; ++s) {
    //     float t = static_cast<float>(s) / steps;


    //     for (int row = 0; row < 3; ++row) {
    //         for (int col = 0; col < 8; ++col) {
    //             if (col < static_cast<int>(startAngles.size()) && row < static_cast<int>(startAngles[col].size())){
    //                 float h = interpolateAngle(270.0f, startAngles[col][row].first, t);
    //                 float m = interpolateAngle(270.0f, startAngles[col][row].second, t);

    //                 clocks[row][col].setInstant(h, m);
    //                 if (row == targetRow && col == targetCol) {
    //                         ClockMotion motion;
    //                         motion.hourAngle = normalize(h);
    //                         motion.minuteAngle = normalize(m);
    //                         sendClockMotionToReceptor(motion);
    //                 }
    //             }
    //         }
    //     }

    //     std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    // }

    int clock_id=0;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 8; ++col) {
            clock_id++;
            if (col < static_cast<int>(startAngles.size()) && row < static_cast<int>(startAngles[col].size())){
                float h = 270.0f;
                float m = 270.0f;

                clocks[row][col].setInstant(h, m);
                if (row == targetRow && col == targetCol) {
                        ClockMotion motion;
                        motion.hourAngle = normalize(h);
                        motion.minuteAngle = normalize(m);
                        motion.clock_id=clock_id;
                        motion.minDir=-1;
                        motion.hourDir=-1;
                        sendClockMotionToReceptor(motion);
                }
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    int previousMinute = currentMinute;

    // Main loop: waits for minute change and triggers animation
    while (1) {

        now = time(0);
        localTime = localtime(&now);
        currentHour = localTime->tm_hour;
        currentMinute = localTime->tm_min;

        if (currentMinute != previousMinute) {
            previousMinute = currentMinute;

            std::string targetText = (currentHour < 10 ? "0" : "") + std::to_string(currentHour) +
                                     (currentMinute < 10 ? "0" : "") + std::to_string(currentMinute);
            auto targetAngles = getTextAngles(targetText);

            // Apply chosen transition effect
            if (transitionType == "words") {
                std::string trans_word = transitionDetail;
                auto wordAngles = getTextAngles(trans_word);
                words(clocks, startAngles, targetAngles, direction, trans_word);
            } 
            else if (transitionType == "pacman") {
                if (direction == 3) direction =1;
                if (direction == 4) direction =2;
                pacman(clocks, targetAngles, direction);
            } 
            else if (transitionType == "wave") {
                int pattern_number = std::stoi(transitionDetail);
                if (direction == 5) {
                    pattern_number = 2;
                }
                wave(clocks, startAngles, targetAngles, direction, pattern_number);
            } 
            else if (transitionType == "stars") {
                int pattern_number = std::stoi(transitionDetail);
                if (direction == 5) {
                    pattern_number = 2;
                }
                stars(clocks, startAngles, targetAngles, direction, pattern_number);
            } 
            else {
                std::cerr << "Error: Unknown transition type. Use -help for valid options.\n";
                return 1;
            }

            startText = targetText;
            startAngles = targetAngles;
        }
    }

    return 0;
}
