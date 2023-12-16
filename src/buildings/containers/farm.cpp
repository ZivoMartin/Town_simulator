#include "farm.h"
#include "../../Game.h"

Farm::Farm(Game *game, Xy coord) : Container(game->get_img("farm"), game, coord){
    init_stat();
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.farm = this;
    setting->add_info_zone(new InfoZone(game, {coord.x+10, coord.y+90}, {240, 30}, "Nb max of citizen here: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->get_info_zone("lvl")->set_base_text("Farm level ");
    game->set_max_citizen(game->get_max_citizen()+max_worker[0]);
    setting->get_reverse()->get_info_zone("header")->set_base_text("Farm");
    init_common_value();
}

Farm::~Farm(){}


bool Farm::add_worker(){
    if(nb_worker < max_worker[lvl]){
        nb_worker += 1;
        return true;
    }
    return false;
}

bool Farm::pull_worker(){
    if(nb_worker>0){
        nb_worker -= 1;
        return true;
    }
    return false;
}

void Farm::init_stat(){
    type = "farm";
    max_worker = {7, 8, 10, 12};
    price_to_up = {90, 150, 200};
    value_for_sold = {20, 60, 100, 150};
}