#include "shop.h"
#include "../Game.h"


Shop::Shop(Game *game, Xy coord) : Building(game->get_img("shop"), game->get_view()->get_scene(), {coord.x - game->get_img_size("shop")->x/2, coord.y - game->get_img_size("shop")->y/2}){
    this->game = game;
}
Shop::~Shop(){}
