#include "type_transitions/type_transitions.h"  // Inclure le fichier d'animation Pac-Man
#include <ctime>
#include <iostream>

void printHelp() {
    std::cout << "Usage: ./clock_project <direction (1-3)> <transitionType> <transitionDetail>\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  <direction>: Indique la direction de la transition\n";
    std::cout << "    - 1 : De gauche à droite \n";
    std::cout << "    - 2 : De droite à gauche \n";
    std::cout << "    - 3 : De haut en bas\n\n";
    
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

    // Récupération des arguments
    int direction = std::stoi(argv[1]);  // Convertir en int
    std::string transitionType = argv[2];  // Type de transition
    std::string transitionDetail = argv[3];  // Détails supplémentaires

    sf::RenderWindow window(sf::VideoMode(1000, 400), "Clock Transition", sf::Style::Close);

    // Création des horloges
    std::vector<std::vector<Clock>> clocks(3, std::vector<Clock>(8, Clock(0, 0))); 
    float startX = 100, startY = 50;
    float spacingX = 120, spacingY = 120;

    for (int row = 0; row < 3; row++) {  
        for (int col = 0; col < 8; col++) {  
            clocks[row][col] = Clock(startX + col * spacingX, startY + row * spacingY);
        }
    }

    // Récupération de l'heure actuelle
    time_t now = time(0);
    struct tm *localTime = localtime(&now);
    int currentHour = localTime->tm_hour;  
    int currentMinute = localTime->tm_min; 

    std::string startText = (currentHour < 10 ? "0" : "") + std::to_string(currentHour) + 
                            (currentMinute < 10 ? "0" : "") + std::to_string(currentMinute);
    auto startAngles = getTextAngles(startText);

    // Affichage initial de l'heure
    for (size_t col = 0; col < 8; col++) {  
        for (size_t row = 0; row < 3; row++) {  
            if (col < startAngles.size() && row < startAngles[col].size()) {
                clocks[row][col].update(startAngles[col][row].first, startAngles[col][row].second);
            }
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

    int previousMinute = currentMinute;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        now = time(0);
        localTime = localtime(&now);
        currentHour = localTime->tm_hour;
        currentMinute = localTime->tm_min;

        if (currentMinute != previousMinute) {
            previousMinute = currentMinute;

            // Détermination de la nouvelle heure cible
            std::string targetText = (currentHour < 10 ? "0" : "") + std::to_string(currentHour) + 
                                     (currentMinute < 10 ? "0" : "") + std::to_string(currentMinute);
            auto targetAngles = getTextAngles(targetText);

            // Appliquer la transition choisie
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

        window.clear(sf::Color::White);
        for (const auto& rowVec : clocks) {
            for (const auto& clock : rowVec) {
                clock.draw(window);
            }
        }
        window.display();
    }

    return 0;
}
