#include "house.h"
#include "../Game.h"

int House::max_worker[4] = {6, 8, 10, 12};


House::House(Game *game, Xy coord) : Building(game->get_img("house"), game, coord){
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.house = this;
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+44}, *game->get_img_size("more"), &Game::close_current_setting, "more_worker", game->get_img("more")));
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+84}, *game->get_img_size("less"), &Game::close_current_setting, "less_worker", game->get_img("less")));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+44}, {130, 30}, "Add a worker", game->get_color("increase_worker"), RECT, "add_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+84}, {130, 30}, "Pull a worker", game->get_color("decrease_worker"), RECT, "pull_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+123}, {150, 30}, "Nb worker: ", game->get_color("increase_worker"), RECT, "nb_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+255, coord.y+28}, {120, 30}, "House level ", game->get_color("lvl_info"), RECT, "lvl"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+162}, {150, 30}, "Nb max worker: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->add_img(new GraphicsPixmapItem(game->get_img("house"), game->get_view()->get_scene(), {coord.x+306, coord.y+123}));
    setting->get_info_zone("nb_worker")->set_value(0.0);
    setting->get_info_zone("nb_max_worker")->set_value(static_cast<float>(max_worker[0]));
    setting->get_info_zone("lvl")->set_value(0.0);
}
House::~House(){}
