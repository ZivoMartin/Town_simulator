#ifndef safe_farm
#define safe_farm

#include "container.h"

class Game;

class Farm: public Container{

public:
    Farm(Game *game, Xy coord);
    ~Farm();
    bool add_worker() override;
    bool pull_worker() override;
    void init_stat() override;
};

#endif