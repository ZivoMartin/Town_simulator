#include "house.h"
#include "../Game.h"

int House::max_worker[4] = {6, 8, 10, 12};


House::House(Game *game, Xy coord) : Building(game->get_img("house"), game, coord){
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.house = this;
    setting->add_info_zone(new InfoZone(game, {coord.x+255, coord.y+28}, {120, 30}, "House level ", game->get_color("lvl_info"), RECT, "lvl"));
    setting->add_info_zone(new InfoZone(game, {coord.x+10, coord.y+90}, {240, 30}, "Nb max of citizen here: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->add_img(new GraphicsPixmapItem(game->get_img("house"), game->get_view()->get_scene(), {coord.x+306, coord.y+123}));
    setting->get_info_zone("nb_worker")->set_value(0.0);
    setting->get_info_zone("nb_max_worker")->set_value(static_cast<float>(max_worker[0]));
    setting->get_info_zone("lvl")->set_value(0.0);
}
House::~House(){}
