#include <iostream>
#include <string>
#include "confirm.h"

bool confirm(std::string_view message) {
    std::string answer;
    do {
        std::cout << message;
        std::cin >> answer;
        for (char& c : answer) {
            c = toupper(c);
        }
    } while (answer != "Y" && answer != "N");

    return answer == "Y";
}