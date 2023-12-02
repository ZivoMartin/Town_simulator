#include "field.h"
#include "../Game.h"

Field::Field(Game *game, Xy coord) : Building(game->get_img("field"), game->get_view()->get_scene(), coord){
    this->game = game;
}
Field::~Field(){

}
