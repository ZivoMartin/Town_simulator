#include "house.h"
#include "../Game.h"


House::House(Game *game, Xy coord) : Building(game->get_img("house"), game->get_view()->get_scene(), coord){
    this->game = game;
}
House::~House(){}
