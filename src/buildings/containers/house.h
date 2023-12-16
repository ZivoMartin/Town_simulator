#ifndef safe_house
#define safe_house

#include "container.h"

class Game;

class House: public Container{

public:
    House(Game *game, Xy coord);
    ~House();
    void init_stat() override;
};

#endif