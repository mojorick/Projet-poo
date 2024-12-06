#include "GameOfLife.hpp"
#include <iostream>
#include <string>

int main() {
    int cellSize = 10; // Taille des cellules
    int delay;
    std::string inputFile;

    std::cout << "Entrez le chemin du fichier d'entrée (ex: grille.txt) : ";
    std::getline(std::cin, inputFile);

    std::cout << "Entrez le délai entre deux itérations (ms) : ";
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
