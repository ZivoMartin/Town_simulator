#include "house.h"
#include "../Game.h"


House::House(Game *game, Xy coord) : Building(game->get_img("house"), game, coord){
}
House::~House(){}
