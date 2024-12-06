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
    Grid grid;
    FileHandler fileHandler;
    std::vector<std::string> previousStates;
    int cellSize;
    int width, height;

public:
    GameOfLife(const std::string& filename, int cellSize);
    void run();

    void render(sf::RenderWindow& window) override;
    void updateGrid() override;
};

#endif // GAME_OF_LIFE_HPP
