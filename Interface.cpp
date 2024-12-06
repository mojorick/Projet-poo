#include "Interface.hpp"

void Interface::setDelay(double newDelay) {
    delay = newDelay;
    std::cout << "Nouveau délai défini : " << delay << " ms.\n";
}

double Interface::getDelay() const {
    return delay;
}

void Interface::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            setDelay(getDelay() + 5); // Augmenter de 5 ms
        } else if (event.key.code == sf::Keyboard::Down) {
            setDelay(std::max(5.0, getDelay() - 5)); // Ne pas aller en dessous de 5 ms
        }
        std::cout << "Délai actuel : " << delay << " ms\n";
    }
}
