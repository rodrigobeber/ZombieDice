#pragma once

#include <string>

struct Player {
    std::string name;
    unsigned int brains;
    bool operator==(const Player& other) const {
        return this->name == other.name;
    }
};
