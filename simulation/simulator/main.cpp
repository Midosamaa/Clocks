#include "type_transitions/type_transitions.h"
#include <ctime>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <cstring>

void printHelp() {
    std::cout << "Usage: ./clock_project <direction (1-3)> <transitionType> <transitionDetail>\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  <direction>: Indique la direction de la transition\n";
    std::cout << "    - 1 : De droite à gauche \n";
    std::cout << "    - 2 : De gauche à droite \n";
    std::cout << "    - 3 : De bas vers haut\n";
    std::cout << "    - 4 : De haut en bas\n\n";

    std::cout << "  <transitionType>: Type d'effet appliqué lors du changement de minute\n";
    std::cout << "    - 'pacman'  : Animation Pac-Man mangeant l'ancien affichage (transitionDetail = NULL)\n";
    std::cout << "    - 'wave'    : Animation en vagues (transitionDetail = nombre de vagues)\n";
    std::cout << "    - 'stars'   : Animation avec des étoiles (transitionDetail = nombre d'étoiles affichées)\n";
    std::cout << "    - 'words'   : Affichage d'un mot temporaire avant d'afficher l'heure (transitionDetail = mot à afficher)\n\n";

    std::cout << "Exemples d'utilisation:\n";
    std::cout << "  ./clock_project 1 pacman NULL       # Transition Pac-Man vers la droite\n";
    std::cout << "  ./clock_project 2 wave 5            # Effet de vague avec 5 vagues vers la gauche\n";
    std::cout << "  ./clock_project 3 stars 10          # Affichage de 10 étoiles vers le haut\n";
    std::cout << "  ./clock_project 1 words HELLO       # Affichage du mot 'HELLO' avant l'heure\n";
}

std::string waitForSupervisorMessage() {
    int server_fd;
    sockaddr_in server_addr{}, client_addr{};
    socklen_t len = sizeof(client_addr);
    const int PORT = 6000;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 1);

    std::cout << "[MAIN] Waiting for supervisor...\n";
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &len);
    char buffer[1024] = {0};
    int bytesRead = read(client_fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';

    std::string msg(buffer);
    close(client_fd);
    close(server_fd);
    return msg;
}

std::string parseReceivedTime(const std::string& raw) {
    size_t pos = raw.find("\"time\":\"");
    if (pos != std::string::npos) {
        return raw.substr(pos + 8, 4);
    }
    return "0000";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Erreur : Nombre d'arguments insuffisant.\nUtilisez -help pour plus d'informations.\n";
        return 1;
    }

    std::string firstArg = argv[1];
    if (firstArg == "-help") {
        printHelp();
        return 0;
    }

    if (argc < 4) {
        std::cerr << "Usage incorrect ! Utilisez -help pour voir les options disponibles.\n";
        return 1;
    }

    int direction = std::stoi(argv[1]);
    std::string transitionType = argv[2];
    std::string transitionDetail = argv[3];

    sf::RenderWindow window(sf::VideoMode(1000, 400), "Clock Transition", sf::Style::Close);

    std::vector<std::vector<Clock>> clocks(3, std::vector<Clock>(8, Clock(0, 0))); 
    float startX = 100, startY = 100;
    float spacingX = 120, spacingY = 120;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 8; col++) {
            clocks[row][col] = Clock(startX + col * spacingX, startY + row * spacingY);
        }
    }

   // Wait for initial time from supervisor before initializing angles
    std::string firstMessage = waitForSupervisorMessage();
    std::string startText = parseReceivedTime(firstMessage);
    auto startAngles = getTextAngles(startText);

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 8; col++) {
            clocks[row][col].setInstant(270, 270);
        }
    }

    window.clear(sf::Color::White);
    for (const auto& rowVec : clocks) {
        for (const auto& clock : rowVec) {
            clock.draw(window);
        }
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Animate to current time (only hands move)
    for (size_t col = 0; col < 8; col++) {  
        for (size_t row = 0; row < 3; row++) {  
            if (col < startAngles.size() && row < startAngles[col].size()) {
                if (row == targetRow && col == targetCol) {
                    clocks[row][col].update_with_send(startAngles[col][row].first, startAngles[col][row].second, window);
                } else {
                    clocks[row][col].update(startAngles[col][row].first, startAngles[col][row].second, window);
                }
            }
        }
    }

    while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    std::string received = waitForSupervisorMessage();
    std::string targetText = parseReceivedTime(received);

    if (targetText != startText) {
        auto targetAngles = getTextAngles(targetText);

        if (transitionType == "words") {
            std::string trans_word = transitionDetail;
            auto wordAngles = getTextAngles(trans_word);
            words(window, clocks, startAngles, targetAngles, direction, trans_word);
        } 
        else if (transitionType == "pacman") {
            pacman(window, clocks, targetAngles, direction);
        } 
        else if (transitionType == "wave") {
            int pattern_number = std::stoi(transitionDetail);
            wave(window, clocks, startAngles, targetAngles, direction, pattern_number);
        } 
        else if (transitionType == "stars") {
            int pattern_number = std::stoi(transitionDetail);
            stars(window, clocks, startAngles, targetAngles, direction, pattern_number);
        } 
        else {
            std::cerr << "Erreur : Type de transition inconnu. Utilisez -help pour voir les options valides.\n";
            return 1;
        }

        startText = targetText;
        startAngles = targetAngles;
    }
}
    return 0;
}
