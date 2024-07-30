#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "game.h"
#include <vector>
#include <utility>

using namespace std;

class Game;

class TextObserver : public Observer {
    shared_ptr<Game> trackGame;
    public:
        TextObserver(shared_ptr<Game> game);
        void notify() override;
        ~TextObserver();
};

#endif
