#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

// Classe représentant une horloge analogique
class Clock {
public:
    sf::CircleShape circle;
    sf::RectangleShape hourHand, minuteHand;
    sf::Vector2f position;
    float targetHourAngle, targetMinuteAngle;
    float currentHourAngle, currentMinuteAngle;
    bool animating = false;
    sf::Clock animationTimer;
    float animationDuration = 1.5f;

    Clock(float x, float y) {
        position = sf::Vector2f(x, y);
        
        circle.setRadius(40);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setOrigin(40, 40);
        circle.setPosition(position);
        
        hourHand.setSize(sf::Vector2f(4, 25));
        hourHand.setFillColor(sf::Color::Red);
        hourHand.setOrigin(2, 20);
        hourHand.setPosition(position);
        
        minuteHand.setSize(sf::Vector2f(2, 35));
        minuteHand.setFillColor(sf::Color::Red);
        minuteHand.setOrigin(1, 30);
        minuteHand.setPosition(position);
    }
    
    void setTargetTime(float hourAngle, float minuteAngle) {
        targetHourAngle = hourAngle;
        targetMinuteAngle = minuteAngle;
        currentHourAngle = hourHand.getRotation();
        currentMinuteAngle = minuteHand.getRotation();
        animating = true;
        animationTimer.restart();
    }
    
    void update() {
        if (animating) {
            float t = animationTimer.getElapsedTime().asSeconds() / animationDuration;
            if (t >= 1.0f) {
                animating = false;
                hourHand.setRotation(targetHourAngle);
                minuteHand.setRotation(targetMinuteAngle);
            } else {
                hourHand.setRotation(currentHourAngle + 360 * t + (targetHourAngle - currentHourAngle) * t);
                minuteHand.setRotation(currentMinuteAngle + 360 * t + (targetMinuteAngle - currentMinuteAngle) * t);
            }
        }
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(circle);
        window.draw(hourHand);
        window.draw(minuteHand);
    }
};

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

    int lastMinute = -1;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        int hours = localTime->tm_hour;
        int minutes = localTime->tm_min;
        
        if (minutes != lastMinute) {
            lastMinute = minutes;
            std::array<int, 4> currentDigits = {hours / 10, hours % 10, minutes / 10, minutes % 10};
            for (int d = 0; d < 4; ++d) {
                for (int i = 0; i < 3; ++i) {
                    int leftIndex = (d * 2) * 3 + i;
                    int rightIndex = leftIndex + 3;
                    clocks[leftIndex].setTargetTime(digitConfigurations[currentDigits[d]][i].first,
                                                    digitConfigurations[currentDigits[d]][i].second);
                    clocks[rightIndex].setTargetTime(digitConfigurations[currentDigits[d]][i + 3].first,
                                                     digitConfigurations[currentDigits[d]][i + 3].second);
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