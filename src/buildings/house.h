#ifndef safe_house
#define safe_house
#include "building.h"

class Game;

class House: public Building{

public:
    House(Game *game, Xy coord);
    ~House();

private:
    Game *game;

};

#endif