#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

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
    sf::RenderWindow window(sf::VideoMode(1000, 400), "Clock Digits", sf::Style::Close);
    window.clear(sf::Color::White);
    
    std::vector<Clock> clocks;
    float startX = 100, startY = 50;
    float spacingX = 90, spacingY = 90;

    int transition_time = 25;
    int transition_step = 10;
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            clocks.emplace_back(startX + i * spacingX, startY + j * spacingY);
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            clocks.emplace_back(440 + startX + i * spacingX, startY + j * spacingY);
        }
    }

    // Ajouter les horloges des secondes
    Clock topSecondClock(455, 90); // Position ajustée
    Clock bottomSecondClock(455, 195); // Position ajustée

    
    int lastMinute = -1;
    int secondPhase = 0;
    sf::Clock secondTimer;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(transition_time));
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        
        int hours = localTime->tm_hour;
        int minutes = localTime->tm_min;
        int seconds = localTime->tm_sec;
        


        if (minutes != lastMinute) {
            lastMinute = minutes;
            
            for (int step = 0; step <= 360; step += transition_step) {
                window.clear(sf::Color::White);
                for (auto& clock : clocks) {
                    clock.setTime(step, step);
                    clock.draw(window);
                }
                window.display();
                std::this_thread::sleep_for(std::chrono::milliseconds(transition_time));
            }
        }
        
        std::array<int, 4> currentDigits = {hours / 10, hours % 10, minutes / 10, minutes % 10};
        
        window.clear(sf::Color::White);
        
        for (int d = 0; d < 4; ++d) { 
            for (int i = 0; i < 3; ++i) { 
                int leftIndex = (d * 2) * 3 + i;
                int rightIndex = leftIndex + 3;
                
                float hourAngle = digitConfigurations[currentDigits[d]][i].first;
                float minuteAngle = digitConfigurations[currentDigits[d]][i].second;
                
                clocks[leftIndex].setTime(hourAngle, minuteAngle);
                clocks[rightIndex].setTime(digitConfigurations[currentDigits[d]][i + 3].first, 
                                            digitConfigurations[currentDigits[d]][i + 3].second);
                
                clocks[leftIndex].draw(window);
                clocks[rightIndex].draw(window);
            }
        }
        
        if (secondTimer.getElapsedTime().asSeconds() >= 0.5f) {
            secondPhase = (secondPhase + 1) % 4;
            secondTimer.restart();
        }
        
        float secondAngles[4] = {0, 180, 180, 0};
        topSecondClock.setTime(secondAngles[secondPhase], secondAngles[secondPhase]);
        bottomSecondClock.setTime(secondAngles[(secondPhase + 2) % 4], secondAngles[(secondPhase + 2) % 4]);
        
        topSecondClock.draw(window);
        bottomSecondClock.draw(window);
        
        window.display();
    }
    return 0;
}
