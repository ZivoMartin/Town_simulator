#include "shop.h"
#include "../Game.h"


Shop::Shop(Game *game, Xy coord) : Building(game->get_img("shop"), game, coord){
    value_per_worker = 2;
    setting_union = new build_tab_case;
    setting_union->type = SHOP;
    setting_union->building.shop = this;
}
Shop::~Shop(){}
