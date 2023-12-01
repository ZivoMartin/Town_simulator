#ifndef safe_app
#define safe_app

#include <QApplication>
#include "../Game.h"

class Application : public QApplication{

public:
    Application(int argc, char **argv);
    ~Application();
    void set_game(Game *game);

private:
    Game *game;
};

#endif