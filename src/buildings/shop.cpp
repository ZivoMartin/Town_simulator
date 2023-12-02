#include "shop.h"
#include "../Game.h"


Shop::Shop(Game *game, Xy coord) : Building(game->get_img("field"), game->get_view()->get_scene(), coord){
    this->game = game;
}
Shop::~Shop(){}
