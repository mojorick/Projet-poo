#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>
#include <vector>
#include <filesystem>

class FileHandler {
private:
    std::string outputFolder; // Nom du dossier de sortie

public:
    FileHandler(const std::string& baseName); // Initialise le gestionnaire avec un dossier de sortie
    void saveGridToFile(const std::vector<std::vector<int>>& grid, int iteration) const; // Sauvegarde une grille dans un fichier
};

#endif // FILEHANDLER_HPP
