#ifndef GAME_OF_LIFE_HPP
#define GAME_OF_LIFE_HPP

#include "Grid.hpp"
#include "FileHandler.hpp"
#include "Interface.hpp"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <iostream>

class GameOfLife : public Interface {
private:
    Grid grid;                              // Instance de la grille
    FileHandler fileHandler;                // Gestionnaire de fichiers
    std::vector<std::string> previousStates; // Ensemble des états précédents
    int delay;                              // Délai entre les itérations
    int cellSize;                           // Taille des cellules pour l'interface
    int width, height;   // Dimensions de la grille        

public:
    GameOfLife(const std::string& filename, int cellSize, int delayMs); // Initialise le jeu
    void run();                   // Implémente la logique complète (console + interface)

    // Implémentations des méthodes virtuelles de Interface
    void render(sf::RenderWindow& window) override;
    void updateGrid() override;
    void setDelay(int newDelay) override;
    int getDelay() const override;
};

#endif // GAME_OF_LIFE_HPP
