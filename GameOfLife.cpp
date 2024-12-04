#include "GameOfLife.hpp"
#include <iostream>
#include <string>

GameOfLife::GameOfLife(const std::string& filename, int cellSize, int delayMs)
    : grid(filename), fileHandler(std::filesystem::path(filename).stem()), delay(delayMs), cellSize(cellSize) {
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
    // Dessiner les lignes de la grille
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

    window.draw(gridLines);
    window.display();
}



void GameOfLife::updateGrid() {
    grid.update();
}

void GameOfLife::setDelay(int newDelay) {
    delay = newDelay;
}

int GameOfLife::getDelay() const {
    return delay;
}

void GameOfLife::run() {
    sf::RenderWindow window(sf::VideoMode(width * cellSize, height * cellSize), "Jeu de la Vie");

    while (window.isOpen()) {
        // Gestion des événements SFML
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return; // Quitter la boucle
            }
        }

        // Affichage console
        std::cout << "Iteration " << iteration << ":\n"; // Utilise iteration directement
        grid.display();

        // Sauvegarde de l'état actuel de la grille
        fileHandler.saveGridToFile(grid.getGrid(), iteration);

        // Affichage graphique
        render(window);

        // Mise à jour de la grille
        updateGrid();

        std::string currentState = grid.toString();

        if (!previousStates.empty()) {
            if (previousStates.back() == currentState) {
                std::cout << "La grille n'évolue plus, arrêt de la simulation.\n";
                break; // Quitte la boucle
            }
        }

        previousStates.push_back(currentState);

        if (previousStates.size() > 100) {
            previousStates.erase(previousStates.begin());
        }


        // Pause entre deux itérations
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        iteration++; // Incrémente correctement
    }

    // Garder la fenêtre ouverte après la fin de la simulation
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Réafficher l'état final dans la fenêtre graphique
        render(window);
    }
}

