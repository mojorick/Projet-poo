#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Interface {
protected:
<<<<<<< HEAD
    int iteration = 0;     // Compteur d'itérations
    double delay = 500.0;  // Délai initial (ms)
=======
    int iteration = 0;   // Compteur d'itérations
    double delay;    // Délai initial par défaut (ms)
>>>>>>> 0b9f01c28d6736a984ff2b0ea914db116e743289

public:
    virtual void render(sf::RenderWindow& window) = 0; // Méthode virtuelle pure
    virtual void updateGrid() = 0;                    // Méthode virtuelle pure
    virtual ~Interface() = default;

    void setDelay(double newDelay); // Change le délai
    double getDelay() const;        // Retourne le délai
    void handleInput(const sf::Event& event); // Gère les entrées utilisateur
};

#endif // INTERFACE_HPP
