#include "Interface.hpp"

void Interface::setDelay(int newDelay) {
    delay = newDelay;
    std::cout << "Nouveau délai défini : " << delay << " ms." << std::endl;
}

int Interface::getDelay() const {
    return delay;
}

void Interface::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            // Augmenter le délai de 10 ms
            setDelay(getDelay() + 5);
            std::cout << "Délai augmenté : " << getDelay() << " ms\n";
        } else if (event.key.code == sf::Keyboard::Down) {
            // Diminuer le délai de 10 ms, mais s'assurer qu'il ne soit pas négatif
            int newDelay = std::max(0, getDelay() -5);
            setDelay(newDelay);
            std::cout << "Délai diminué : " << getDelay() << " ms\n";
        }
    }
}
