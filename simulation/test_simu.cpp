#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include <array>
#include <iostream>

#define DEBUG_DIGITS // Décommente cette ligne pour tester le mode debug

class Clock {
public:
    sf::CircleShape circle;
    sf::RectangleShape hourHand, minuteHand;
    sf::Vector2f position;
    float targetHourAngle, targetMinuteAngle;
    float currentHourAngle, currentMinuteAngle;
    bool animating = true;
    sf::Clock animationTimer;
    float animationDuration = 0.5f;
    bool enableAnimation = true; // Nouveau flag

    Clock(float x, float y) {
        position = sf::Vector2f(x, y);
        
        circle.setRadius(40);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setOrigin(40, 40);
        circle.setPosition(position);
        
        hourHand.setSize(sf::Vector2f(4, 25));
        hourHand.setOrigin(2, 20);
        hourHand.setPosition(position);
        
        minuteHand.setSize(sf::Vector2f(2, 35));
        minuteHand.setOrigin(1, 30);
        minuteHand.setPosition(position);
    }
    
    void setTargetTime(float hourAngle, float minuteAngle, bool animate = true) {
        targetHourAngle = hourAngle;
        targetMinuteAngle = minuteAngle;
        currentHourAngle = hourHand.getRotation();
        currentMinuteAngle = minuteHand.getRotation();
        enableAnimation = animate;
        
        if (animate) {
            animating = true;
            animationTimer.restart();
        } else {
            animating = false;
            hourHand.setRotation(hourAngle);
            minuteHand.setRotation(minuteAngle);
        }

        if (hourAngle == 315 && minuteAngle == 315) {
            hourHand.setFillColor(sf::Color::White);
            minuteHand.setFillColor(sf::Color::White);
        } else {
            hourHand.setFillColor(sf::Color::Red);
            minuteHand.setFillColor(sf::Color::Red);
        }
    }
    
    void update() {
        if (animating && enableAnimation) {
            float t = animationTimer.getElapsedTime().asSeconds() / animationDuration;
            if (t >= 1.0f) {
                animating = false;
                hourHand.setRotation(targetHourAngle);
                minuteHand.setRotation(targetMinuteAngle);
            } else {
                hourHand.setRotation(currentHourAngle + (targetHourAngle - currentHourAngle) * t);
                minuteHand.setRotation(currentMinuteAngle + (targetMinuteAngle - currentMinuteAngle) * t);
            }
        }
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(circle);
        window.draw(hourHand);
        window.draw(minuteHand);
    }
};

// Configuration des chiffres, similaire à ce que tu as déjà
std::map<int, std::vector<std::pair<float, float>>> digitConfigurations = {
    {0, {{90, 180}, {0, 180}, {90, 0}, {270, 180}, {0, 180}, {270, 0}}},
    {1, {{315, 315}, {45, 45}, {315, 315}, {180, 225}, {180, 0}, {0, 0}}},
    {2, {{90, 90}, {180, 90}, {0, 90}, {180, 270}, {0, 270}, {270, 270}}},
    {3, {{90, 90}, {90, 90}, {90, 90}, {180, 270}, {0, 270}, {0, 270}}},
    {4, {{180, 180}, {0, 90}, {315, 315}, {180, 180}, {0, 180}, {0, 0}}},
    {5, {{180, 90}, {0, 90}, {90, 90}, {270, 270}, {180, 270}, {0, 270}}},
    {6, {{180, 90}, {0, 180}, {0, 90}, {270, 270}, {180, 270}, {0, 270}}},
    {7, {{180, 90}, {315, 315}, {315, 315}, {180, 270}, {180, 0}, {0, 0}}},
    {8, {{180, 90}, {0, 90}, {90, 0}, {180, 270}, {0, 270}, {270, 0}}},
    {9, {{180, 90}, {0, 90}, {90, 90}, {180, 270}, {0, 270}, {0, 270}}},
    {10, {{180, 90}, {0, 90}, {0, 0}, {180, 270}, {0, 270}, {315, 315}}}, // P
    {11, {{180, 180}, {180, 0}, {90, 0}, {315, 315}, {315, 315}, {270, 270}}}, // L
    {12, {{180, 180}, {90, 0}, {90, 90}, {180, 180}, {270, 0}, {270, 0}}}, // y
    {13, {{180, 180}, {90, 0}, {90, 0}, {315, 315}, {270, 270}, {270, 270}}}, // t
    {14, {{90, 180}, {90, 0}, {90, 0}, {270, 270}, {270, 270}, {270, 270}}}, // E
    {15, {{90, 180}, {180, 0}, {90, 0}, {270, 270}, {315, 315}, {270, 270}}}, //C
    {16, {{180, 180}, {90, 0}, {0, 0}, {180, 180}, {270, 0}, {0, 0}}}, //H
    {17, {{315, 315}, {45, 135}, {315, 315}, {135, 225}, {315, 315}, {135, 315}}}, // left half heart
    {18, {{225, 135}, {315, 315}, {225,45}, {315, 315}, {315, 225}, {315, 315}}} //right half heart
};

// Fonction principale
int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 400), "Clock Digits", sf::Style::Close);
    window.clear(sf::Color::White);
    
    std::vector<Clock> clocks;
    float startX = 100, startY = 50;
    float spacingX = 90, spacingY = 90;

    // Crée les horloges pour afficher les chiffres
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 3; ++j) {
            clocks.emplace_back(startX + i * spacingX, startY + j * spacingY);
        }
    }



    // Variables pour le décalage progressif des colonnes
    sf::Clock shiftTimer;
    float shiftDuration = 0.0f; // Durée pour décaler les parties des colonnes
    int currentColumn = 7; // Commence à la 8e colonne (indice 7)
    int totalColumns = 8; // Nombre total de colonnes
    // Ajout d'un nouveau sf::Clock pour suivre l'incrémentation
    sf::Clock cntClock;
    float cntIncrementDuration = 0.33f; // Durée entre chaque incrémentation de cnt (en secondes)
    int cnt = 0; // Valeur initiale
    int counter=0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Vérifie si le temps écoulé depuis le dernier incrément est supérieur à la durée spécifiée
        if (cntClock.getElapsedTime().asSeconds() >= cntIncrementDuration) {
            // Incrémente cnt de 1, et remet-le à 7 lorsqu'il atteint 8 (cycle entre 7 et 8)
            if (cnt < 3) {
                ++cnt;
            } else {
                cnt = 0; // Réinitialiser à 7 pour recommencer le cycle
            }
            if (counter < 7) {
                counter++;
            } else {
                counter = 0; // Réinitialiser à 7 pour recommencer le cycle
            }

            // Réinitialise le timer pour la prochaine incrémentation
            cntClock.restart();
        }
        
        // Mise à jour du décalage des parties des chiffres
        if (shiftTimer.getElapsedTime().asSeconds() > shiftDuration) {
            std::array<int, 8> currentDigits = {10, 0, 11, 12, 13, 14, 15, 16};
            if (counter >= 0 && counter <= 3) {
               
                    for (int d = 0; d < 1; ++d) { // Parcours de currentDigits
                        for (int i = 0; i < 3; ++i) {
                            // Partie gauche : colonne 8 à 6 (déplacement horizontal progressif)
                            clocks[3*(0*d+2*cnt)+(2*(4*d + i) -(i +d))].setTargetTime(digitConfigurations[currentDigits[(d+counter)]][i].first,
                                                                    digitConfigurations[currentDigits[(d+counter)]][i].second, false);
                        }  
                        for (int i = 0; i < 3; ++i) {
                            // Partie gauche : colonne 8 à 6 (déplacement horizontal progressif)
                            clocks[3*(0*d+2*cnt)+(3+2*(4*d + i) -(i +d))].setTargetTime(digitConfigurations[currentDigits[(d+counter)]][i+3].first,
                                                                    digitConfigurations[currentDigits[(d+counter)]][i+3].second, false);
                        }
                    }
            }
        
        if (counter >= 4 && counter <= 8) {
               
            for (int d = 0; d < 1; ++d) { // Parcours de currentDigits
                for (int i = 0; i < 3; ++i) {
                    // Partie gauche : colonne 8 à 6 (déplacement horizontal progressif)
                    clocks[3*(1*d+2*cnt)+(2*(1*d + i) -(i +d))].setTargetTime(digitConfigurations[currentDigits[(d+counter)]][i].first,
                                                            digitConfigurations[currentDigits[(d+counter)]][i].second, false);
                }  
                for (int i = 0; i < 3; ++i) {
                    // Partie gauche : colonne 8 à 6 (déplacement horizontal progressif)
                    clocks[3*(1*d+2*cnt)+(3+2*(1*d + i) -(i +d))].setTargetTime(digitConfigurations[currentDigits[(d+counter)]][i+3].first,
                                                            digitConfigurations[currentDigits[(d+counter)]][i+3].second, false);
                }
            }
        }
}

        window.clear(sf::Color::White);
        for (auto& clock : clocks) {
            clock.update();
            clock.draw(window);
        }

        window.display();
    }
    return 0;
}
