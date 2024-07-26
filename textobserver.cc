#include "textobserver.h"
#include "game.h"
#include <vector>
#include <iostream>

using namespace std;

TextObserver::TextObserver(Game *game) :
trackGame{game} {
    trackGame->attach(this);
}

void TextObserver::notify() {
    for (int i = 0; i < 8; ++i) {
        cout << 8-i << ' ';
        for (int j = 0; j < 8; ++j) {
            if (trackGame->getState(i, j) != '$') { //piece exists on square
            cout << trackGame->getState(i, j);
            }
            else {
                // determine colour of board square
                if (i % 2 == 0 && j % 2 == 0) { //_ for black, ' ' for white
                    cout << ' ';
                }
                else if (i % 2 == 1 && j % 2 == 1) {
                    cout << ' ';
                }
                else {
                    cout << '_';
                }
            }
        }
        
        cout << "\n";
    }
    cout << "\n";
    cout << "  abcdefgh" << "\n";
}

TextObserver::~TextObserver() {}
