#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Game.h"
#include "Player.h"
#include "Piece.h"
#include "textobserver.h"



int main () {
    int whiteScore = 0;
    int blackScore = 0;

    // Game* game = new Game();
    Game *game = new Game;
    new TextObserver(game);
    game->notifyObservers();

    std::string command;

    while (std::cin >> command) {
        // Parse the command and execute the appropriate action
        if (command == "game") {

            if(game->status == "Running") {
                delete game;
                game = new Game(); //create a fresh game and the delete the old one
            }


            // Extract player types and start a new game
            std::string whitePlayer = command.substr(5, command.find(" ", 5) - 5);
            std::string blackPlayer = command.substr(command.find(" ", 5) + 1);
            game->setUpGame(whitePlayer, blackPlayer);
        }

        else if (command == "setup") {
            game->setup();
        }
        
        
        // else if (command == "move") {
        //     game->makeMove();

        //     if(game->status == "WhiteWon") {
        //         whiteScore++;
        //         //blah blah get status and update score 

        //         //this game is done!
        //         delete game;
        //         game = new Game(); //create a fresh game and the delete the old one
        //     }

        // } else if (command == "resign") {
        //     if (game) {
        //         // Handle resign command
        //         game->resign();
        //     } else {
        //         std::cout << "No game in progress.\n";
        //     }
        // } 
    }

}


