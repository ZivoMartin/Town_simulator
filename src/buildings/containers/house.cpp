#include "house.h"
#include "../../Game.h"

House::House(Game *game, Xy coord) : Container(game->get_img("house"), game, coord){
    init_stat();
    setting_union = new build_tab_case;
    setting_union->type = HOUSE;
    setting_union->building.house = this;
    setting->add_info_zone(new InfoZone(game, {coord.x+10, coord.y+90}, {240, 30}, "Nb max of citizen here: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->get_info_zone("lvl")->set_base_text("House level ");
    game->set_max_citizen(game->get_max_citizen()+max_worker[0]);
    setting->get_reverse()->get_info_zone("header")->set_base_text("House");
    init_common_value();
    setting->get_reverse()->get_tab_info("advanced_stat")->set_base_text({0, 3}, "Nombre max\n d'habitant'");
}

House::~House(){}

void House::init_stat(){
    type = "house";
    max_worker = {7, 8, 10, 12};
    price_to_up = {90, 150, 200};
    value_for_sold = {20, 60, 100, 150};
}