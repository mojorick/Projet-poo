#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Interface {
protected:
    int iteration = 0;     // Compteur d'itérations
    double delay = 500.0;  // Délai initial (ms)

public:
    virtual void render(sf::RenderWindow& window) = 0; // Méthode virtuelle pure
    virtual void updateGrid() = 0;                    // Méthode virtuelle pure
    virtual ~Interface() = default;

    void setDelay(double newDelay); // Change le délai
    double getDelay() const;        // Retourne le délai
    void handleInput(const sf::Event& event); // Gère les entrées utilisateur
};

#endif // INTERFACE_HPP
