#ifndef safe_field
#define safe_field

#include "building.h"

class Game;

class Field: public Building{

public:
    Field(Game *game, Xy coord);
    ~Field();
    bool add_worker() override;
    bool pull_worker() override;
    float get_efficiency() override;
    int get_value_for_sold() override;
    
private:
    static int max_worker[4];
    static float value_per_worker[4];
    static int value_for_sold[4];
    static int price_to_up[3];
};

#endif