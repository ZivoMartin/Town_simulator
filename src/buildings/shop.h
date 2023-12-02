#ifndef safe_shop
#define safe_shop
#include "building.h"

class Game;

class Shop: public Building{

public:
    Shop(Game *game, Xy coord);
    ~Shop();

private:
    Game *game;

};

#endif