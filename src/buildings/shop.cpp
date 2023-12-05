#include "shop.h"
#include "../Game.h"


Shop::Shop(Game *game, Xy coord) : Building(game->get_img("shop"), game, coord){
    value_per_worker = 2;
}
Shop::~Shop(){}
