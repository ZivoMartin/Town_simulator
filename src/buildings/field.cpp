#include "field.h"
#include "../Game.h"

int Field::max_worker[4] = {6, 8, 10, 12};
float Field::value_per_worker[4] = {0.3, 0.4, 0.5, 0.6};
int Field::price_to_up[3] = {120, 150, 200};
int Field::value_for_sold[4] = {100, 120, 150, 200};

Field::Field(Game *game, Xy coord) : Building(game->get_img("field"), game, coord){
    setting_union = new build_tab_case;
    setting_union->type = FIELD;
    setting_union->building.field = this;
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+44}, *game->get_img_size("more"), &Game::add_worker, "more_worker", game->get_img("more")));
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+84}, *game->get_img_size("less"), &Game::remove_worker, "less_worker", game->get_img("less")));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+44}, {130, 30}, "Add a worker", game->get_color("increase_worker"), RECT, "add_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+84}, {130, 30}, "Pull a worker", game->get_color("decrease_worker"), RECT, "pull_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+123}, {150, 30}, "Nb worker: ", game->get_color("increase_worker"), RECT, "nb_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+245, coord.y+10}, {120, 30}, "Field level ", game->get_color("lvl_info"), RECT, "lvl"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+162}, {150, 30}, "Nb max worker: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->add_img(new GraphicsPixmapItem(game->get_img("field"), game->get_view()->get_scene(), {coord.x+306, coord.y+100}));
    setting->get_info_zone("nb_worker")->set_value(0.0);
    setting->get_info_zone("nb_max_worker")->set_value(static_cast<float>(max_worker[0]));
    setting->get_info_zone("lvl")->set_value(0.0);

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

float Field::get_efficiency(){
    return nb_worker*value_per_worker[lvl];
}

int Field::get_value_for_sold(){
    return value_for_sold[lvl];
}