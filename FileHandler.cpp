#include "FileHandler.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace fs = std::filesystem;

FileHandler::FileHandler(const std::string& baseName) {
    outputFolder = baseName + "_out";
    if (!fs::exists(outputFolder)) {
        fs::create_directory(outputFolder);
    }
}

void FileHandler::saveGridToFile(const std::vector<std::vector<int>>& grid, int iteration) const {
    std::ostringstream fileName;
    fileName << outputFolder << "/iteration_" << std::setfill('0') << std::setw(3) << iteration + 1 << ".txt";

    std::ofstream file(fileName.str());
    if (!file.is_open()) {
        throw std::runtime_error("Impossible de sauvegarder dans le fichier : " + fileName.str());
    }

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            file << (cell ? "1" : "0") << " ";
        }
        file << "\n";
    }
}
