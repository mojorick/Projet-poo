#include "GameOfLife.hpp"
#include <iostream>
#include <string>

int main() {
    int cellSize = 20; // Taille des cellules graphiques
    int delay;
    std::string inputFile;

    std::cout << "Entrez le chemin du fichier de grille d'entrée (ex: grille.txt) : ";
    std::getline(std::cin, inputFile);

    std::cout << "Entrez le délai entre deux itérations (en millisecondes, ex: 500) : ";
    std::cin >> delay;

    try {
        GameOfLife game(inputFile, cellSize);
        game.setDelay(delay);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
        return 1;
    }

    return 0;
}