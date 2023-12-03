#include "house.h"
#include "../Game.h"


House::House(Game *game, Xy coord) : Building(game->get_img("house"), game->get_view()->get_scene(), {coord.x - game->get_img_size("house")->x/2, coord.y - game->get_img_size("house")->y/2}){
    this->game = game;
}
House::~House(){}
