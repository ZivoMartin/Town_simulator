#ifndef safe_shop
#define safe_shop
#include "building.h"

class Game;

class Shop: public Building{

public:
    Shop(Game *game, Xy coord);
    ~Shop();
    bool add_worker() override;
    bool pull_worker() override;

private:
    static int max_worker[4];
};

#endif