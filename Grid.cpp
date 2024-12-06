#include "Grid.hpp"
#include <fstream>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<int>(cols, 0));
    nextGrid.resize(rows, std::vector<int>(cols, 0));
}

Grid::Grid(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier d'entrée.");
    }

    file >> rows >> cols;
    if (rows <= 0 || cols <= 0) {
        throw std::runtime_error("Dimensions de la grille invalides.");
    }

    grid.resize(rows, std::vector<int>(cols, 0));
    nextGrid.resize(rows, std::vector<int>(cols, 0));

    // Lire les données et vérifier leur cohérence
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> grid[i][j])) {
                throw std::runtime_error("Fichier d'entrée incomplet ou mal formaté.");
            }
            // Vérifier que les valeurs sont valides (par exemple, 0, 1, 2 ou 3)
            if (grid[i][j] < 0 || grid[i][j] > 3) {
                throw std::runtime_error("Valeur de cellule invalide détectée dans le fichier d'entrée.");
            }
        }
    }

    // Vérifier s'il y a des données supplémentaires dans le fichier
    if (file >> extraData) {
        throw std::runtime_error("Fichier d'entrée contient des données supplémentaires inattendues.");
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> grid[i][j];
        }
    }


    file.close();
}

int Grid::countNeighbors(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Ignorer la cellule elle-même

            // Gestion des bordures cycliques
            int nx = (x + i + rows) % rows; // Modulo pour "revenir" en ligne
            int ny = (y + j + cols) % cols; // Modulo pour "revenir" en colonne

            // Ajouter au décompte si c'est une cellule vivante ou une cellule obstacle vivante
            if (grid[nx][ny] == 1 || grid[nx][ny] == 2) {
                count++;
            }
        }
    }
    return count;
}



void Grid::update() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Si c'est une cellule obstacle, on ne modifie pas son état
            if (grid[i][j] == 2 || grid[i][j] == 3) {
                nextGrid[i][j] = grid[i][j];
                continue;
            }

            int neighbors = countNeighbors(i, j);
            if (grid[i][j] == 1) { // Cellule vivante
                nextGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else { // Cellule morte
                nextGrid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
    grid = nextGrid; // Mettre à jour la grille
}

void Grid::display() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == 1) {
                std::cout << "1 "; // Cellule vivante
            } else if (cell == 0) {
                std::cout << "0 "; // Cellule morte
            } else if (cell == 2) {
                std::cout << "X "; // Cellule obstacle vivante
            } else if (cell == 3) {
                std::cout << "Y "; // Cellule obstacle morte
            }
        }
        std::cout << "\n";
    }
    std::cout << std::string(20, '=') << "\n";
}

std::string Grid::toString() const {
    std::string str = "";
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            str += std::to_string(cell);
        }
    }
    return str;
}

const std::vector<std::vector<int>>& Grid::getGrid() const {
    return grid;
}
