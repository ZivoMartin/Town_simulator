#include "shop.h"
#include "../../Game.h"

Shop::Shop(Game *game, Xy coord) : Generator(game->get_img("shop"), game, coord){
    init_stat();
    setting_union = new build_tab_case;
    setting_union->type = SHOP;
    setting_union->building.shop = this;
    setting->get_info_zone("lvl")->set_base_text("Shop level ");    
    setting->get_reverse()->get_info_zone("header")->set_base_text("Shop");
    init_common_value();
}
Shop::~Shop(){}

    
bool Shop::add_worker(){
    if(nb_worker < max_worker[lvl]){
        nb_worker += 1;
        setting->get_info_zone("nb_worker")->set_value(setting->get_info_zone("nb_worker")->get_value() +1);   
        game->update_gold_ratio();
        return true;
    }
    return false;
}

bool Shop::pull_worker(){
    if(nb_worker>0){
        nb_worker -= 1;
        setting->get_info_zone("nb_worker")->set_value(setting->get_info_zone("nb_worker")->get_value() -1);
        game->update_gold_ratio();
        return true;
    }
    return false;
}  


void Shop::init_stat(){
    type = "shop";
    max_worker = {6, 8, 10, 12};
    value_per_worker = {0.3, 0.3, 0.4, 0.5};
    price_to_up = {100, 200, 300};
    value_for_sold = {100, 120, 150, 200};
}