#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Game.h"
#include "Player.h"
#include "Piece.h"



int main () {
    Game* game = nullptr;

    std::string command;
    while (true) {
        std::getline(std::cin, command);

        // Parse the command and execute the appropriate action
        if (command.substr(0, 4) == "game") {
            // Extract player types and start a new game
            std::string whitePlayer = command.substr(5, command.find(" ", 5) - 5);
            std::string blackPlayer = command.substr(command.find(" ", 5) + 1);
            game = new Game(whitePlayer, blackPlayer);
        } else if (command.substr(0, 4) == "move") {
            if (game) {
                // Handle move command
                game->makeMove(command);
            } else {
                std::cout << "No game in progress.\n";
            }
        } else if (command.substr(0, 6) == "resign") {
            if (game) {
                // Handle resign command
                game->resign();
            } else {
                std::cout << "No game in progress.\n";
            }
        } else if (command.substr(0, 5) == "setup") {
            if (game) {
                // Handle setup mode
                game->setupMode();
            } else {
                std::cout << "No game in progress.\n";
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command.\n";
        }
    }

}
