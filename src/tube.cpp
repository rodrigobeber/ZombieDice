#include <stdexcept>
#include "gen.h"
#include "tube.h"

Tube::Tube() {
    for (int i = 0; i < 6; ++i) {
        m_dices.emplace_back(std::make_unique<GreenDice>());
    }
    for (int i = 0; i < 4; ++i) {
        m_dices.emplace_back(std::make_unique<YellowDice>());
    }
    for (int i = 0; i < 3; ++i) {
        m_dices.emplace_back(std::make_unique<RedDice>());
    }
}

std::unique_ptr<Dice> Tube::extractDice() {
    if (m_dices.empty()) {
        throw std::runtime_error("No dices left in the tube");
    }
    std::uniform_int_distribution<std::size_t> dist(0, m_dices.size() - 1);
    // if not the last one element, swap the the last one
    if (std::size_t index = dist(gen); index != m_dices.size() - 1) {
        std::swap(m_dices[index], m_dices.back());
    }

    auto dice = std::move(m_dices.back());
    m_dices.pop_back();

    return dice;
}

void Tube::putBack(std::unique_ptr<Dice>& dice) {
    m_dices.push_back(std::move(dice));
}

void Tube::putBack(std::vector<std::unique_ptr<Dice>>& putDices) {
    for (auto& dice : putDices) {
        putBack(dice);
    }
}

size_t Tube::getNumOfDices() const {
    return m_dices.size();
}