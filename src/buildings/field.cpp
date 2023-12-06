#include "field.h"
#include "../Game.h"

Field::Field(Game *game, Xy coord) : Building(game->get_img("field"), game, coord){
    value_per_worker = 3;
    setting_union = new build_tab_case;
    setting_union->type = FIELD;
    setting_union->building.field = this;
    setting->add_button(new PushButton(game, "+", {static_cast<int>(coord.x*1.25), static_cast<int>(coord.y*1.1)}, game->get_color("building_add_worker_button"), {15, 15}, &Game::close_setting, "more_worker"));
    setting->add_button(new PushButton(game, "-", {static_cast<int>(coord.x*1.25), static_cast<int>(coord.y*1.15)}, game->get_color("building_less_worker_button"), {15, 15}, &Game::close_setting, "less_worker"));
    setting->add_info_zone(new InfoZone(game, {static_cast<int>(coord.x*1.05), static_cast<int>(coord.y*1.1)}, {30, 30}, "Add a worker", color_map["set_info_color"], RECT));
}

Field::~Field(){

}
