#include "Interface.hpp"

void Interface::setDelay(double newDelay) {
    if(newDelay<1.00){
        throw std::invalid_argument("delai inferieur a zero");
    }
    delay = newDelay;
    std::cout << "Nouveau délai défini : " << delay << " ms." << std::endl;

}

double Interface::getDelay() const {
    return delay;
}


void Interface::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            setDelay(getDelay() + 5); // Augmenter de 5 ms
        } else if (event.key.code == sf::Keyboard::Down) {
            double newDelay = std::max(1.00, getDelay() - 5); // Assurez-vous qu'il ne descende pas en dessous de 0.1 ms
            setDelay(newDelay);
        }
        std::cout << "Délai actuel : " << getDelay() << " ms\n";
    }
}
