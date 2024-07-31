#include "graphicsobserver.h"
#include "window.h"
#include <vector>
#include <cctype>
#include <string>

using namespace std;

GraphicsObserver::GraphicsObserver(Game *game) :
trackGame{move(game)} {
    trackGame->attach(this);
}

void GraphicsObserver::notify() {

    for (int j = 0; j < 8; ++j) {
    w.drawString(7+20, (j+1)*20+12, to_string(8-(j)));
        for (int i = 0; i < 8; ++i) {
             if (i % 2 == 0 && j % 2 == 0) { 
                    w.fillRectangle((i+2)*20, (j+1)*20, 20, 20, 0); // white squares
                }
                else if (i % 2 == 1 && j % 2 == 1) {
                    w.fillRectangle((i+2)*20, (j+1)*20, 20, 20, 0); // white squares
                }
                else {
                    w.fillRectangle((i+2)*20, (j+1)*20, 20, 20, 3); // black squares
                }
            if (trackGame->getState(j, i) != '$') { //piece exists on square
                std::string charOutput {trackGame->getState(j, i)};
                w.drawString((i+2)*20+7, (j+1)*20+12, charOutput);
            }
        }
    }
    for (int i = 0; i < 8; ++i) {
        char letter = 'a' +i;
        string strLetter {letter};
        w.drawString((i+2)*20+7,9*20+12, strLetter);

    }
}


GraphicsObserver::~GraphicsObserver() {}

