#pragma once

#include <random>
#include <vector>

enum class DiceFace {
    // do not change the order!
    Brain, Footsteps, Shotgun
};

std::string diceFaceToString(DiceFace face);

class Dice {
protected:
    std::discrete_distribution<> m_dis;
    Dice(const std::initializer_list<double>& probabilities);
public:
    virtual ~Dice() = default;
    DiceFace roll();
    virtual std::string getColorName() const = 0;
};

class GreenDice : public Dice {
public:
    GreenDice();
    std::string getColorName() const override;
};

class RedDice : public Dice {
public:
    RedDice();
    std::string getColorName() const override;
};

class YellowDice : public Dice {
public:
    YellowDice();
    std::string getColorName() const override;
};
