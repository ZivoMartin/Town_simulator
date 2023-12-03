#include "field.h"
#include "../Game.h"

Field::Field(Game *game, Xy coord) : Building(game->get_img("field"), game->get_view()->get_scene(), {coord.x - game->get_img_size("field")->x/2, coord.y - game->get_img_size("field")->y/2}){
    this->game = game;
}
Field::~Field(){

}
