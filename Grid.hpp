#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class Grid {
private:
    int extraData;
protected:
    std::vector<std::vector<int>> grid;       // Grille actuelle
    std::vector<std::vector<int>> nextGrid;   // Grille pour la prochaine itération
    int rows, cols;                           // Dimensions de la grille
public:
    int countNeighbors(int x, int y) const;   // Compte les voisins vivants autour d'une cellule
    Grid(int rows, int cols);                 // Constructeur par dimensions
    Grid(const std::string& filename);        // Constructeur par fichier
    void update();                            // Met à jour la grille
    void display() const;                     // Affiche la grille dans le terminal
    std::string toString() const;             // Convertit la grille en chaîne
    const std::vector<std::vector<int>>& getGrid() const; // Retourne la grille (lecture seule)
};

#endif // GRID_HPP
