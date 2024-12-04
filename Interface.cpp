#include "Interface.hpp"
#include <iostream>

void Interface::requestDelay() {
    int newDelay;
    std::cout << "Entrez le délai commun entre deux itérations (en millisecondes, ex: 500) : ";
    std::cin >> newDelay;
    setDelay(newDelay); // Mise à jour du délai avec la méthode virtuelle pure
}