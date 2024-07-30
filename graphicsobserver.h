#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"
#include "window.h"
#include "game.h"
#include <vector>

class GraphicsObserver : public Observer {
    std::shared_ptr<Game> trackGame;
    Xwindow w{240, 220};
    public:
        GraphicsObserver(std::shared_ptr<Game> game);
        void notify() override;
        ~GraphicsObserver();
};

#endif
