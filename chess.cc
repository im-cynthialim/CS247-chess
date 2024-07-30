#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "game.h"
#include "player.h"
#include "piece.h"
#include "textobserver.h"
#include <utility>
#include "graphicsobserver.h"

int main () {
    float whiteScore = 0;
    float blackScore = 0;

    // Game *game = new Game;
    
    // std::shared_ptr<Game> game = std::make_unique<Game>();
    std::shared_ptr<Game> game = std::make_shared<Game>();
    new TextObserver(game);
    new GraphicsObserver(game);
    game->notifyObservers();

    std::string command;

    while (std::cin >> command) {   
        // Parse the command and execute the appropriate action
        if (command == "game") {
            if(game->status != NOTSTARTED) { //if the game has already started and you run "game" --> then replace the game
                // delete game; // Clean up the old game
                game = std::make_shared<Game>(); // Create a fresh game
                new TextObserver(game);
                new GraphicsObserver(game);

              
            }
            std::string whitePlayer, blackPlayer;
            std::cin >> whitePlayer >> blackPlayer;
            // Extract player types and start a new game
            game->setUpGame(whitePlayer, blackPlayer);
            game->notifyObservers();
        }
        else if (command == "setup") {
            if (game->status == NOTSTARTED) {
                game->setup();
            } else {
                std::cout << "No game in progress.\n";
            }
        }
        else if (command == "move") {
            if (game->status == RUNNING) { 
                game->makeMove();
                if (game->status == WHITEWINS) {
                    whiteScore++;
                    // delete game; // Game is done
                    game = std::make_shared<Game>(); // Create a fresh game
                    // new TextObserver(game);
                    // new GraphicsObserver(game);
                } else if (game->status == BLACKWINS) {
                    blackScore++;
                    // delete game; // Game is done
                    game = std::make_shared<Game>(); // Create a fresh game
                    // new TextObserver(game);
                    // new GraphicsObserver(game);
                } else if (game->status == DRAW) {
                    whiteScore = whiteScore + 0.5;
                    blackScore = blackScore + 0.5;
                    // delete game; // Game is done
                    game = std::make_shared<Game>(); // Create a fresh game
                    // new TextObserver(game);
                    // new GraphicsObserver(game);
                }
            } else {
                std::cout << "No game in progress.\n";
            }
        } 
        else if (command == "resign") {
            if (game->status == RUNNING) {
                game->resign();
                if (game->status == BLACKWINS) {
                    blackScore++;
                } else {
                    whiteScore++;
                }
                //update who won
                // delete game; // Game is done
                game = std::make_shared<Game>(); // Create a fresh game
                // new TextObserver(game);
                // new GraphicsObserver(game);
            } else {
                std::cout << "No game in progress.\n";
            }
        } 
    }

    std::cout << "WhiteScore: " << whiteScore << "\n";
    std::cout << "BlackScore: " << blackScore << "\n";
    delete game;
}
