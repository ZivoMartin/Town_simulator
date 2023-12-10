#include "house.h"
#include "../Game.h"

int House::max_worker[4] = {7, 8, 10, 12};
int House::price_to_up[3] = {90, 150, 200};
int House::value_for_sold[4] = {20, 60, 100, 150};

House::House(Game *game, Xy coord) : Building(game->get_img("house"), game, coord){
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.house = this;
    setting->add_info_zone(new InfoZone(game, {coord.x+245, coord.y+10}, {120, 30}, "House level ", game->get_color("lvl_info"), RECT, "lvl"));
    setting->add_info_zone(new InfoZone(game, {coord.x+10, coord.y+90}, {240, 30}, "Nb max of citizen here: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->add_img(new GraphicsPixmapItem(game->get_img("house"), game->get_view()->get_scene(), {coord.x+306, coord.y+100}));
    setting->get_info_zone("lvl")->set_value(1.0);
    setting->get_info_zone("nb_max_worker")->set_value(max_worker[0]);
    game->set_max_citizen(game->get_max_citizen()+max_worker[0]);
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

float House::get_efficiency(){return 0;}

int House::get_value_for_sold(){
    return value_for_sold[lvl];
}