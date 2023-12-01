#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <random>
#include "view/GraphicsView.h"


struct Xy{
    int x;
    int y;
};

class Game : public QMainWindow{

public: 
    Game(GraphicsView *view);
    ~Game();
    int get_iter();

private:
    GraphicsView *view;
    unsigned int iter = 0;
};

int random(int min, int max);
int get_dist(Xy *coord1, Xy *coord2);

#endif
