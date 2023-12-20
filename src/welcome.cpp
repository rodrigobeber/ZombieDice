#include <fstream>
#include <iostream>
#include <string>
#include "welcome.h"

void Welcome::sayWelcome() {
    std::ifstream file("README.md"); // Assuming README.md is in the current directory

    if (!file) {
        std::cerr << "Unable to open file README.md" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}