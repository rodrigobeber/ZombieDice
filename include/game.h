#pragma once

#include <vector>
#include "player.h"

#define WIN_SCORE 13
#define SLEEP std::this_thread::sleep_for(std::chrono::seconds(1))

class Game {
private:
    std::vector<Player> m_allPlayers;
    void reset();
    void orderAllPlayers(const Player& initialPlayer);
    std::vector<Player> calcWinners(const std::vector<Player>& players) const;
    void playTurn(Player &player);
public:
    Game (std::vector<Player> allPlayers): m_allPlayers(allPlayers) {}
    Player& play(const Player &initialPlayer);
};