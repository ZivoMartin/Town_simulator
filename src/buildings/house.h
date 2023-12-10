#ifndef safe_house
#define safe_house

#include "building.h"

class Game;

class House: public Building{

public:
    House(Game *game, Xy coord);
    ~House();
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