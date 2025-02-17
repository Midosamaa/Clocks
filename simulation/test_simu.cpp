#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <map>

// Classe représentant une horloge analogique
// Classe représentant une horloge analogique
class Clock {
public:
    sf::CircleShape circle;
    sf::RectangleShape hourHand, minuteHand;
    sf::Vector2f position;
    
    Clock(float x, float y) {
        position = sf::Vector2f(x, y);
        
        // Création du cadran
        circle.setRadius(40);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setOrigin(40, 40);
        circle.setPosition(position);
        
        // Aiguille des heures
        hourHand.setSize(sf::Vector2f(4, 25));
        hourHand.setFillColor(sf::Color::Red);
        hourHand.setOrigin(2, 20);
        hourHand.setPosition(position);
        
        // Aiguille des minutes
        minuteHand.setSize(sf::Vector2f(2, 35));
        minuteHand.setFillColor(sf::Color::Red);
        minuteHand.setOrigin(1, 30);
        minuteHand.setPosition(position);
    }
    
    void setTime(float hourAngle, float minuteAngle) {
        hourHand.setRotation(hourAngle);
        minuteHand.setRotation(minuteAngle);
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(circle);
        window.draw(hourHand);
        window.draw(minuteHand);
    }
};


// Configuration des chiffres avec les horloges
std::map<int, std::vector<std::pair<float, float>>> digitConfigurations = {
    /*
    1 4
    2 5
    3 6
    */
    {0, {{90, 180}, {0, 180}, {90, 0}, {270, 180}, {0, 180}, {270, 0}}},
    {1, {{315, 315}, {45, 45}, {315, 315}, {180, 225}, {180, 0}, {0, 0}}},
    {2, {{90, 90}, {180, 90}, {0, 90}, {180, 270}, {0, 270}, {270, 270}}},
    {3, {{90, 90}, {90, 90}, {90, 90}, {180, 270}, {0, 270}, {0, 270}}},
    {4, {{180, 180}, {0, 90}, {315, 315}, {180, 180}, {0, 180}, {0, 0}}},
    {5, {{180, 90}, {0, 90}, {90, 90}, {270, 270}, {180, 270}, {0, 270}}},
    {6, {{180, 90}, {0, 180}, {0, 90}, {270, 270}, {180, 270}, {0, 270}}},
    {7, {{180, 90}, {315, 315}, {315, 315}, {180, 270}, {180, 0}, {0, 0}}},
    {8, {{180, 90}, {0, 90}, {90, 0}, {180, 270}, {0, 270}, {270, 0}}},
    {9, {{180, 90}, {0, 90}, {90, 90}, {180, 270}, {0, 270}, {0, 270}}}
};


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 400), "Clock Digits", sf::Style::Close);
    window.clear(sf::Color::White);
    
    std::vector<Clock> clocks;
    float startX = 100, startY = 50;
    float spacingX = 90, spacingY = 90; // Espacement ajusté pour aligner les horloges
    
    // Création des horloges (3 lignes x 8 colonnes)
    for (int i = 0; i < 8; ++i) { // 8 colonnes (2 colonnes par chiffre)
        for (int j = 0; j < 3; ++j) { // 3 lignes par colonne
            clocks.emplace_back(startX + i * spacingX, startY + j * spacingY);
        }
    }

    std::array<int, 4> currentDigits = {1, 2, 3, 4};
    
    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
        
    //     window.clear(sf::Color::White);
        
    //     // Affichage des chiffres sous forme 3x8
    //     for (int d = 0; d < 4; ++d) { 
    //         for (int i = 0; i < 3; ++i) { // 3 horloges de la première colonne du chiffre
    //             int leftIndex = (d * 2) * 3 + i;  // Index dans clocks pour la première colonne
    //             int rightIndex = leftIndex + 3;   // Index pour la deuxième colonne du chiffre

    //             float hourAngle = digitConfigurations[currentDigits[d]][i].first;
    //             float minuteAngle = digitConfigurations[currentDigits[d]][i].second;

    //             if (hourAngle != -1 && minuteAngle != -1) {
    //                 clocks[leftIndex].setTime(hourAngle, minuteAngle);
    //                 clocks[rightIndex].setTime(digitConfigurations[currentDigits[d]][i + 3].first, 
    //                                            digitConfigurations[currentDigits[d]][i + 3].second);
    //             }

    //             clocks[leftIndex].draw(window);
    //             clocks[rightIndex].draw(window);
    //         }
    //     }
        
    //     window.display();
    // }
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Récupérer l'heure actuelle
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        
        int hours = localTime->tm_hour;
        int minutes = localTime->tm_min;
        
        // Extraire les chiffres des heures et minutes
        std::array<int, 4> currentDigits = {
            hours / 10, hours % 10, 
            minutes / 10, minutes % 10
        };

        window.clear(sf::Color::White);
        
        // Affichage des chiffres sous forme 3x8
        for (int d = 0; d < 4; ++d) { 
            for (int i = 0; i < 3; ++i) { 
                int leftIndex = (d * 2) * 3 + i;
                int rightIndex = leftIndex + 3;

                float hourAngle = digitConfigurations[currentDigits[d]][i].first;
                float minuteAngle = digitConfigurations[currentDigits[d]][i].second;

                if (hourAngle != -1 && minuteAngle != -1) {
                    clocks[leftIndex].setTime(hourAngle, minuteAngle);
                    clocks[rightIndex].setTime(digitConfigurations[currentDigits[d]][i + 3].first, 
                                            digitConfigurations[currentDigits[d]][i + 3].second);
                }

                clocks[leftIndex].draw(window);
                clocks[rightIndex].draw(window);
            }
        }
        
        window.display();
    }
    return 0;
}
