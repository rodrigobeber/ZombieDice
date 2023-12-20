#pragma once

#include <vector>
#include <string>
#include "player.h"

class InitialInput {
private:
    static Player* getPlayerByName(const std::vector<Player>& players, const std::string& name);
public:
    static int readNumOfPlayers();
    static std::vector<Player> readPlayerList(const int qty);
    static Player& readInitialPlayer(const std::vector<Player>& players);
};
