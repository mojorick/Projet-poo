#include "GameOfLife.hpp"
#include <iostream>
#include <thread>
#include <chrono>

GameOfLife::GameOfLife(const std::string& filename, int cellSize)
    : grid(filename), fileHandler(std::filesystem::path(filename).stem()), cellSize(cellSize) {
    width = grid.getGrid()[0].size();
    height = grid.getGrid().size();
}

void GameOfLife::render(sf::RenderWindow& window) {
    window.clear();

    sf::RectangleShape cell(sf::Vector2f(cellSize - 2.0f, cellSize - 2.0f)); // Marges pour espacement
    const auto& gridData = grid.getGrid();

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            cell.setPosition(y * cellSize, x * cellSize);

            // Couleur en fonction de l'état
            switch (gridData[x][y]) {
                case 1: cell.setFillColor(sf::Color::White); break; // Vivante
                case 0: cell.setFillColor(sf::Color::Black); break; // Morte
                case 2: cell.setFillColor(sf::Color::Blue); break;  // Obstacle vivant
                case 3: cell.setFillColor(sf::Color::Red); break;   // Obstacle mort
            }
            window.draw(cell);
        }
    }
    window.display();
}

void GameOfLife::updateGrid() {
    grid.update();
}

void GameOfLife::run() {
    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            handleInput(event); // Gestion des entrées clavier
        }

        std::cout << "Iteration " << iteration << ":\n";
        grid.display();
        fileHandler.saveGridToFile(grid.getGrid(), iteration);

        render(window);
        updateGrid();

        // Détection des états répétitifs
        std::string currentState = grid.toString();
        if (!previousStates.empty() && previousStates.back() == currentState) {
            std::cout << "La grille n'évolue plus, arrêt de la simulation.\n";
            break;
        }

        previousStates.push_back(currentState);

        // Limitation de l'historique des états
        if (previousStates.size() > 100) {
            previousStates.erase(previousStates.begin());
        }

        // Pause entre deux itérations
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(getDelay()));
        iteration++;
    }
}
