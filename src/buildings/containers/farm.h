#ifndef safe_farm
#define safe_farm

#include "container.h"

class Game;

class Farm: public Container{

public:
    Farm(Game *game, Xy coord);
    ~Farm();
    void init_stat() override;
};

#endif