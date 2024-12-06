#include "Grid.hpp"
#include <fstream>

const int Grid::offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<int>(cols, 0));
}

Grid::Grid(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier d'entrée.");
    }

    file >> rows >> cols;
    grid.resize(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> grid[i][j];
        }
    }
    file.close();
}

int Grid::countNeighbors(int x, int y) const {
    int count = 0;
    for (const auto& offset : offsets) {
        int nx = (x + offset[0] + rows) % rows;
        int ny = (y + offset[1] + cols) % cols;
        if (grid[nx][ny] == 1 || grid[nx][ny] == 2) {
            count++;
        }
    }
    return count;
}

void Grid::update() {
    std::vector<std::vector<int>> newGrid = grid;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 2 || grid[i][j] == 3) continue;

            int neighbors = countNeighbors(i, j);
            if (grid[i][j] == 1) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                newGrid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
    grid = std::move(newGrid);
}

void Grid::display() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == 1) {
                std::cout << "\033[32m1 \033[0m"; // Vert
            } else if (cell == 0) {
                std::cout << "0 "; // Mort
            } else if (cell == 2) {
                std::cout << "\033[34mX \033[0m"; // Bleu
            } else if (cell == 3) {
                std::cout << "\033[31mY \033[0m"; // Rouge
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
