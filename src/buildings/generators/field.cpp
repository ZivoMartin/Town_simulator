#include "field.h"
#include "../../Game.h"



Field::Field(Game *game, Xy coord) : Generator(game->get_img("field"), game, coord){
    init_stat();
    setting_union = new build_tab_case;
    setting_union->type = FIELD;
    setting_union->building.field = this;
    setting->get_info_zone("lvl")->set_base_text("Field niveau ");
    setting->get_reverse()->get_info_zone("header")->set_base_text("Field");
    init_common_value();
}

Field::~Field(){

}


bool Field::add_worker(){
    if(nb_worker < max_worker[lvl]){
        nb_worker += 1;
        setting->get_info_zone("nb_worker")->set_value(setting->get_info_zone("nb_worker")->get_value() +1); 
        game->update_food_ratio();  
        return true;
    }
    return false;
}

bool Field::pull_worker(){
    if(nb_worker>0){
        nb_worker -= 1;
        setting->get_info_zone("nb_worker")->set_value(setting->get_info_zone("nb_worker")->get_value() -1);
        game->update_food_ratio();
        return true;
    }
    return false;
}

void Field::init_stat(){
    type = "field";
    max_worker = {6, 8, 10, 12};
    value_per_worker = {0.3, 0.4, 0.5, 0.6};
    price_to_up = {10, 150, 200};
    value_for_sold = {100, 120, 150, 200};
}