#ifndef safe_house
#define safe_house

#include "container.h"

class Game;

class House: public Container{

public:
    House(Game *game, Xy coord);
    ~House();
    bool add_worker() override;
    bool pull_worker() override;
    void init_stat() override;
};

#endif