#ifndef safe_field
#define safe_field

#include "building.h"

class Game;

class Field: public Building{

public:
    Field(Game *game, Xy coord);
    ~Field();

private:
    static int max_worker[4];
};

#endif