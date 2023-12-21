#pragma once

#include <vector>
#include <memory>
#include "tube.h"
#include "dice.h"

class Turn {
private:
    Tube& m_tube;
    unsigned int m_brainsCount{0};
    unsigned int m_shotGunsCount{0};
    std::vector<std::unique_ptr<Dice>> m_brains;
    std::vector<std::unique_ptr<Dice>> m_footSteps;
    std::vector<std::unique_ptr<Dice>> getDicesToPlay();
    void fixTube();
public:
    unsigned int getBrainsCount() const;
    unsigned int getShotGunsCount() const;
    unsigned int getFootStepsCount() const;
    Turn (Tube &tube): m_tube{tube} {}
    void rollDices();
};