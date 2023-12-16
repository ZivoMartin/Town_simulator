#ifndef safe_shop
#define safe_shop
#include "Generator.h"

class Game;

class Shop: public Generator{

public:
    Shop(Game *game, Xy coord);
    ~Shop();
    bool add_worker() override;
    bool pull_worker() override;
    void init_stat() override;
};

#endif