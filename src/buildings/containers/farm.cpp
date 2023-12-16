#include "farm.h"
#include "../../Game.h"

Farm::Farm(Game *game, Xy coord) : Container(game->get_img("farm"), game, coord){
    init_stat();
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.farm = this;
    setting->add_info_zone(new InfoZone(game, {coord.x+10, coord.y+90}, {240, 30}, "Nb max of food here: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->get_info_zone("lvl")->set_base_text("Farm level ");
    game->set_max_food(game->get_max_food()+max_worker[0]);
    setting->get_reverse()->get_info_zone("header")->set_base_text("Farm");
    init_common_value();
    setting->get_reverse()->get_tab_info("advanced_stat")->set_base_text({0, 3}, "Nombre max\n de nourriture'");
}

Farm::~Farm(){}

void Farm::init_stat(){
    type = "farm";
    max_worker = {100, 150, 200, 300};
    price_to_up = {100, 150, 200};
    value_for_sold = {30, 60, 100, 120};
}