#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Interface {
protected:
    int iteration = 0;   // Compteur d'itérations
    int delay = 500;     // Délai initial par défaut (ms)

public:
    virtual void render(sf::RenderWindow& window) = 0; // Méthode virtuelle pure
    virtual void updateGrid() = 0;                    // Méthode virtuelle pure
    void setDelay(int newDelay);              // Implémentation par défaut
    int getDelay() const;                     // Implémentation par défaut


    // Gestion des entrées clavier
    void handleInput(const sf::Event& event); // Gestion générique des entrées

    virtual ~Interface() = default;            // Destructeur virtuel
};

#endif // INTERFACE_HPP
