#include "house.h"
#include "../Game.h"


House::House(Game *game, Xy coord) : Building(game->get_img("house"), game, coord){
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.house = this;
}
House::~House(){}
