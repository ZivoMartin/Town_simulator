#include "container.h"
#include "../../settings_building/settings.h"
#include "../../Game.h"

Container::Container(QPixmap *image, Game *game, Xy coord) : Building(image, game, coord){

}


Container::~Container(){}

void Container::init_reverse(){
    Xy set_pos = setting->get_reverse()->get_pos();
    setting->get_reverse()->add_tab_info(new TabInfo(game, {5, 4}, {set_pos.x, set_pos.y+(game->get_size_setting_building()->y-30*6)}, {80, 30}, "advanced_stat"));
    setting->get_reverse()->get_tab_info("advanced_stat")->set_base_text({0, 3}, "Nombre max\n d'habitant'");
    nb_line = 4;
}

void Container::init_personnal_value(){
    
}