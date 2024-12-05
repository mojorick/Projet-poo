#include "GameOfLife.hpp"
#include <iostream>
#include <string>

// Modifié : pas de délai dans le constructeur
GameOfLife::GameOfLife(const std::string& filename, int cellSize)
    : grid(filename), fileHandler(std::filesystem::path(filename).stem()), cellSize(cellSize) {
    width = grid.getGrid()[0].size();
    height = grid.getGrid().size();
}

void GameOfLife::render(sf::RenderWindow& window) {
    window.clear();

    sf::RectangleShape cell(sf::Vector2f(cellSize - 2.0f, cellSize - 2.0f)); // Marges pour l'espace entre les cellules
    const auto& gridData = grid.getGrid();

    // Dessiner les cellules
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            cell.setPosition(y * cellSize, x * cellSize);

            if (gridData[x][y] == 1) {
                cell.setFillColor(sf::Color::White); // Cellule vivante
            } else if (gridData[x][y] == 0) {
                cell.setFillColor(sf::Color::Black); // Cellule morte
            } else if (gridData[x][y] == 2) {
                cell.setFillColor(sf::Color::Blue); // Obstacle vivant
            } else if (gridData[x][y] == 3) {
                cell.setFillColor(sf::Color::Red); // Obstacle mort
            }

            window.draw(cell);
        }
    }
    /*// Dessiner les lignes de la grille
    sf::VertexArray gridLines(sf::Lines);

    // Lignes horizontales
    for (int i = 0; i <= height; ++i) {
        gridLines.append(sf::Vertex(sf::Vector2f(0, i * cellSize), sf::Color::White));
        gridLines.append(sf::Vertex(sf::Vector2f(width * cellSize, i * cellSize), sf::Color::White));
    }

    // Lignes verticales
    for (int i = 0; i <= width; ++i) {
        gridLines.append(sf::Vertex(sf::Vector2f(i * cellSize, 0), sf::Color::White));
        gridLines.append(sf::Vertex(sf::Vector2f(i * cellSize, height * cellSize), sf::Color::White));
    }

    window.draw(gridLines);*/
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
            handleInput(event); // Gestion des entrées
        }

        std::cout << "Iteration " << iteration << ":\n";
        grid.display();

        fileHandler.saveGridToFile(grid.getGrid(), iteration);
        render(window);
        updateGrid();

        std::string currentState = grid.toString();

        if (!previousStates.empty()) {
            if (previousStates.back() == currentState) {
                std::cout << "La grille n'évolue plus, arrêt de la simulation.\n";
                break;
            }
        }

        previousStates.push_back(currentState);

        if (previousStates.size() > 100) {
            previousStates.erase(previousStates.begin());
        }

        // Utilisation de getDelay() pour la pause
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(getDelay()));
        iteration++;
    }

    // Garder la fenêtre ouverte
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleInput(event);
        }
        render(window);
    }
}

 