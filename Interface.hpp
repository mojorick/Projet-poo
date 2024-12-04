#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Interface {
protected:
    int iteration=0;
public:
    virtual void render(sf::RenderWindow& window) = 0; // Méthode virtuelle pure
    virtual void updateGrid() = 0;                    // Méthode virtuelle pure
    virtual void setDelay(int newDelay) = 0;          // Méthode virtuelle pure
    virtual int getDelay() const = 0;                 // Méthode virtuelle pure


    // Gestion du délai commun
    void requestDelay();

    virtual ~Interface() = default;                  // Destructeur virtuel
};

#endif // INTERFACE_HPP
