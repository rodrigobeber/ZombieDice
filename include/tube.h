#pragma once

#include <vector>
#include <memory>
#include "dice.h"

class Tube {
private:
    std::vector<std::unique_ptr<Dice>> m_dices;
public:
    Tube();
    std::unique_ptr<Dice> extractDice();
    void putBack(std::vector<std::unique_ptr<Dice>>& putDices);
    void putBack(std::unique_ptr<Dice>& dice);
    size_t getNumOfDices() const;
};