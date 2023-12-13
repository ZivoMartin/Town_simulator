#include "field.h"
#include "../Game.h"



Field::Field(Game *game, Xy coord) : Building(game->get_img("field"), game, coord){
    init_stat();
    setting_union = new build_tab_case;
    setting_union->type = FIELD;
    setting_union->building.field = this;
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+50}, *game->get_img_size("more"), &Game::add_worker, "more_worker", game->get_img("more")));
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+92}, *game->get_img_size("less"), &Game::remove_worker, "less_worker", game->get_img("less")));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+50}, {130, 30}, "Add a worker", game->get_color("increase_worker"), RECT, "add_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+92}, {130, 30}, "Pull a worker", game->get_color("decrease_worker"), RECT, "pull_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+133}, {150, 30}, "Nb worker: ", game->get_color("increase_worker"), RECT, "nb_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+175}, {150, 30}, "Nb max worker: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->add_img(new GraphicsPixmapItem(game->get_img("field"), game->get_view()->get_scene(), {coord.x+306, coord.y+100}));
    setting->get_info_zone("nb_worker")->set_value(0.0);
    setting->get_info_zone("lvl")->set_base_text("Field level ");
    setting->get_reverse()->get_info_zone("header")->set_base_text("Field");
    init_reverse_for_efficient_building();
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
    max_worker = {6, 8, 10, 12};
    value_per_worker = {0.3, 0.4, 0.5, 0.6};
    price_to_up = {10, 150, 200};
    value_for_sold = {100, 120, 150, 200};
}