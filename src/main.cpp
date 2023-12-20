#include "welcome.h"
#include "initialinput.h"
#include "confirm.h"
#include "game.h"

int main() {
    Welcome::sayWelcome();
    std::vector<Player> players = InitialInput::readPlayerList(InitialInput::readNumOfPlayers());
    Player& initialPlayer = InitialInput::readInitialPlayer(players);
    Game game = Game(players);
    while (true) {
        Player &winner = game.play(initialPlayer);
        if (confirm("\n\nRestart the game Y/N? ")) {
            initialPlayer = winner;
        } else {
            break;
        }
    }
    return 0;
}
