#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "game.h"
#include <vector>
#include <utility>

using namespace std;

class Game;

class TextObserver : public Observer {
    Game* trackGame;
    public:
        TextObserver(Game* game);
        void notify() override;
        ~TextObserver();
};

#endif
