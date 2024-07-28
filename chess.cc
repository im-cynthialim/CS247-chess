#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "game.h"
#include "player.h"
#include "piece.h"
#include "textobserver.h"



int main () {
    int whiteScore = 0;
    int blackScore = 0;

    Game *game = new Game;
    new TextObserver(game);
    game->notifyObservers();

    std::string command;

    while (std::cin >> command) {
        // Parse the command and execute the appropriate action
        if (command == "game") {

            if(game->status == RUNNING) {
                delete game;
                game = new Game(); //create a fresh game and the delete the old one
            }

            string whitePlayer, blackPlayer;
            cin >> whitePlayer >> blackPlayer;
            // Extract player types and start a new game
            game->setUpGame(whitePlayer, blackPlayer);
            game->notifyObservers();
        }

        else if (command == "setup") {
            game->setup();
        }
        
        
        else if (command == "move") {
            game->makeMove();
            if(game->status == WHITE) {
                whiteScore++;
                delete game; //game is done 
                game = new Game(); //create a fresh game and the delete the old one
            } else if(game->status == BLACK) {
                blackScore++;
                delete game; //game is done 
                game = new Game(); //create a fresh game and the delete the old one
            } else if(game->status == DRAW) {
                whiteScore++;
                blackScore++;
                delete game; //game is done 
                game = new Game(); //create a fresh game and the delete the old one
            }
        } 
        // else if (command == "resign") {
        //     if (game) {
        //         // Handle resign command
        //         game->resign();
        //     } else {
        //         std::cout << "No game in progress.\n";
        //     }
        // } 
    }

}


