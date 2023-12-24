#include <iostream>
#include <limits>
#include "initialinput.h"

int InitialInput::readNumOfPlayers() {
    int numOfPlayers = 0;
    while (true) {
        std::cout << "How many players will participate? ";
        if (!(std::cin >> numOfPlayers)) {
            std::cout << "Type only digits" << std::endl;
            std::cin.clear();
            // ignore rest of line
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (2 <= numOfPlayers && numOfPlayers <= 99) {
            return numOfPlayers;
        }
        std::cout << "The quantity of players must be between 2 and 99" << std::endl;
    }
}

std::vector<Player> InitialInput::readPlayerList(const int qty) {
    std::vector<Player> players;
    for (int i = 0; i < qty; ++i) {
        while (true) {
            std::cout << "Player's " << i + 1 << " name: ";
            std::string name;
            std::cin >> name;
            if (name.length() < 2) {
                std::cout << "The name must have at least two chars" << std::endl;
                continue;
            }
            if (InitialInput::getPlayerByName(players, name)) {
                std::cout << "Name repeated, try another name" << std::endl;
                continue;
            }
            players.push_back(Player{name});
            break;
        }
    }
    return players;
}

Player& InitialInput::readInitialPlayer(const std::vector<Player>& players) {
    while (true) {
        std::cout << "Type the name of the player who said 'Brain' in the zombiest way: ";
        std::string name;
        std::cin >> name;
        if (Player* initialPlayer = InitialInput::getPlayerByName(players, name); initialPlayer) {
            return *initialPlayer;
        }
        std::cout << "Player not found, try again." << std::endl;
    }
}

Player* InitialInput::getPlayerByName(const std::vector<Player>& players, const std::string& name) {
    for (const Player& player : players) {
        if (player.name == name) {
            return const_cast<Player*>(&player);
        }
    }
    return nullptr;
}