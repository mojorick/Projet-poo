#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class Grid {
protected:
    std::vector<std::vector<int>> grid;   // Grille actuelle
    int rows, cols;                       // Dimensions de la grille
    static const int offsets[8][2];       // Décalages pour les voisins

public:
    Grid(int rows, int cols);             // Constructeur par dimensions
    Grid(const std::string& filename);    // Constructeur par fichier

    int countNeighbors(int x, int y) const; // Compte les voisins vivants
    void update();                         // Met à jour la grille
    void display() const;                  // Affiche la grille dans le terminal
    std::string toString() const;          // Convertit la grille en chaîne
    const std::vector<std::vector<int>>& getGrid() const; // Retourne la grille
};

#endif // GRID_HPP
