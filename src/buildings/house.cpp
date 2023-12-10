#include "house.h"
#include "../Game.h"

House::House(Game *game, Xy coord) : Building(game->get_img("house"), game, coord){
    init_stat();
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.house = this;
    setting->add_info_zone(new InfoZone(game, {coord.x+10, coord.y+90}, {240, 30}, "Nb max of citizen here: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->add_img(new GraphicsPixmapItem(game->get_img("house"), game->get_view()->get_scene(), {coord.x+306, coord.y+100}));
    setting->get_info_zone("lvl")->set_base_text("House level ");
    game->set_max_citizen(game->get_max_citizen()+max_worker[0]);
    init_common_value();
}

House::~House(){}


bool House::add_worker(){
    if(nb_worker < max_worker[lvl]){
        nb_worker += 1;
        return true;
    }
    return false;
    }

bool House::pull_worker(){
    if(nb_worker>0){
        nb_worker -= 1;
        return true;
    }
    return false;
}

void House::init_stat(){
    max_worker = {7, 8, 10, 12};
    price_to_up = {90, 150, 200};
    value_for_sold = {20, 60, 100, 150};
}