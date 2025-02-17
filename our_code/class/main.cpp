#include <SFML/Graphics.hpp>
#include <ctime>
#include "features/Clock.h"
#include "transitions/Transition.h"

int main() {
    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(400, 400), "Smooth Clock Animation");

    // Initialisation d’une horloge au centre
    Clock singleClock(200, 200);

    // Création des objets Transition pour l’heure et les minutes
    Transition hourTransition;
    Transition minuteTransition;

    // Définir une heure de départ manuelle pour tester
    int currentHour = 2;
    int currentMinute = 15;

    // Définir une heure cible vers laquelle on veut animer la transition
    int targetHour = 5;
    int targetMinute = 45;

    // **Convertir en angles (-90° pour alignement SFML)**
    float currentHourAngle = ((currentHour % 12) * 30 + (currentMinute * 0.5f)) - 90;
    float currentMinuteAngle = (currentMinute * 6) - 90;

    float targetHourAngle = ((targetHour % 12) * 30 + (targetMinute * 0.5f)) - 90;
    float targetMinuteAngle = (targetMinute * 6) - 90;

    // **Lancer la transition en partant de l’heure actuelle**
    hourTransition.start(currentHourAngle, currentHourAngle, 5.0f);  
    minuteTransition.start(currentMinuteAngle, currentMinuteAngle, 8.0f);

    // Boucle principale pour l'animation
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // **Mettre à jour progressivement les angles**
        float newHourAngle = hourTransition.getAngle() + 0.02f;
        float newMinuteAngle = minuteTransition.getAngle() + 0.5f;

        // **Arrêter l’animation une fois la cible atteinte**
        if (newHourAngle >= targetHourAngle && newMinuteAngle >= targetMinuteAngle) {
            newHourAngle = targetHourAngle;
            newMinuteAngle = targetMinuteAngle;
        } else {
            // Continuer à mettre à jour jusqu'à l'objectif
            hourTransition.start(hourTransition.getAngle(), newHourAngle, 5.0f);
            minuteTransition.start(minuteTransition.getAngle(), newMinuteAngle, 8.0f);
        }

        // Mettre à jour les transitions
        hourTransition.update();
        minuteTransition.update();

        // Appliquer les nouveaux angles à l’horloge
        singleClock.update(hourTransition.getAngle(), minuteTransition.getAngle());

        // Effacer l’écran et dessiner l'horloge mise à jour
        window.clear(sf::Color::White);
        singleClock.draw(window);
        window.display();
    }

    return 0;
}
