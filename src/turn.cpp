#include <iostream>
#include <chrono>
#include <thread>
#include "turn.h"

unsigned int Turn::getBrainsCount() {
    return m_brainsCount;
}

unsigned int Turn::getShotGunsCount() {
    return m_shotGunsCount;
}

unsigned int Turn::getFootStepsCount() {
    return m_footSteps.size();
}

std::vector<std::unique_ptr<Dice>> Turn::getDicesToPlay() {
    std::vector<std::unique_ptr<Dice>> dicesToPlay;
    while (!m_footSteps.empty() && dicesToPlay.size() < 3) {
        dicesToPlay.push_back(std::move(m_footSteps.back()));
        m_footSteps.pop_back();
    }
    while (dicesToPlay.size() < 3) {
        dicesToPlay.push_back(m_tube.extractDice());
    }
    return dicesToPlay;
}

void Turn::fixTube() {
    if (m_tube.getNumOfDices() < 3) {
        std::cout << "Returned " << m_brains.size() << " brain dices(s) to the tube" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        m_tube.putBack(m_brains);
        m_brains.clear();
    }
}

void Turn::rollDices() {
    fixTube();
    std::vector<std::unique_ptr<Dice>> dicesToPlay = getDicesToPlay();
    std::cout << "Rolled dices: ";
    for (std::unique_ptr<Dice>& dice: dicesToPlay) {
        DiceFace face = dice->roll();
        std::cout << "[" << dice->getColorName() << " " << diceFaceToString(face) << "] ";
        if (face == DiceFace::Brain) {
            ++m_brainsCount;
            m_brains.push_back(std::move(dice));
        } else if (face == DiceFace::Footsteps) {
            m_footSteps.push_back(std::move(dice));
        } else {
            ++m_shotGunsCount;
            m_tube.putBack(dice);
        }
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
