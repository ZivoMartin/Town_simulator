#ifndef safe_field
#define safe_field

#include "Generator.h"

class Game;

class Field: public Generator{

public:
    Field(Game *game, Xy coord);
    ~Field();
    bool add_worker() override;
    bool pull_worker() override;
    void init_stat() override;

};

#endif