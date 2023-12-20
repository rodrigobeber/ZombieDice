#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include "game.h"
#include "tube.h"
#include "turn.h"
#include "confirm.h"

void Game::reset() {
    for (Player &player: m_allPlayers) {
        player.brains = 0;
    }
}

void Game::orderAllPlayers(const Player& initialPlayer) {
    auto it = std::find(m_allPlayers.begin(), m_allPlayers.end(), initialPlayer);
   if (it != m_allPlayers.end()) {
        std::rotate(m_allPlayers.begin(), it, m_allPlayers.end());
    }
}

std::vector<Player> Game::calcWinners(const std::vector<Player>& players) {
    unsigned int maxBrains = std::max_element(players.begin(), players.end(),
        [](const Player& a, const Player& b) {
            return a.brains < b.brains;
        })->brains;
    std::vector<Player> winners;
    std::copy_if(players.begin(), players.end(), std::back_inserter(winners),
        [maxBrains](const Player& player) {
            return player.brains == maxBrains;
        });
    return winners;
}

void Game::playTurn(Player &player) {
    Tube tube;
    Turn turn(tube);
    bool keepPlaying = true;
    std::cout << std::endl << player.name << "'s turn" << std::endl;
    SLEEP;
    while (keepPlaying && turn.getShotGunsCount() < 3) {
        turn.rollDices();
        if (turn.getShotGunsCount() >= 3) {
            std::cout << "Limited of 3 shots reached, turn passed" << std::endl;
            SLEEP;
        } else {
            std::cout << "You have " << turn.getBrainsCount() << " brain(s) this turn, totals: " << player.brains + turn.getBrainsCount() <<
                " brain(s), " << turn.getFootStepsCount() << " footstep(s), " << turn.getShotGunsCount() << " shot(s)." << std::endl;
            SLEEP;
            keepPlaying = confirm("Do you want to play 3 more dices Y/N? ");
            if (!keepPlaying) {
                player.brains += turn.getBrainsCount();
            }
        }
    }
    std::cout << player.name << " has " << player.brains << " brain(s)" << std::endl;
    SLEEP;
}

Player& Game::play(const Player &initialPlayer) {
    orderAllPlayers(initialPlayer);
    reset();
    bool finalTurn = false;
    Player* winningPlayer = nullptr;
    while (!finalTurn) {
        for (Player &player : m_allPlayers) {
            playTurn(player);
            if (player.brains >= WIN_SCORE) {
                std::cout << "Reached " << player.brains << " brains!!" << std::endl;
                std::cout << "This is the final turn!" << std::endl;
                SLEEP;
                finalTurn = true;
                winningPlayer = &player;
                break;
            }
        }
    }

    // play final turn
    orderAllPlayers(*winningPlayer);
    bool skip = true;
    for (Player &player: m_allPlayers) {
        if (!skip) {
            playTurn(player);
        } else {
            skip = false;
        }
    }

    // tiebreak
    std::vector<Player> winners = calcWinners(m_allPlayers);
    while (winners.size() > 1) {
        std::cout << std::endl << "The winners are: " << std::endl;
        for (const Player &player : winners) {
            std::cout << player.name << std::endl;
        }
        // play another turn
        for (Player &player: winners) {
            playTurn(player);
        }
        winners = calcWinners(winners);
        SLEEP;
    }

    // winner
    auto itWinner = std::find(m_allPlayers.begin(), m_allPlayers.end(), winners[0]);
    Player& winner = *itWinner;
    std::cout << std::endl << "The winner is " << winner.name << std::endl;
    SLEEP;

    return winner;
}