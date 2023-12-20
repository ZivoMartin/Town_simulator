#include "Generator.h"
#include "../../settings_building/settings.h"
#include "../../Game.h"

Generator::Generator(QPixmap *image, Game *game, Xy coord) : Building(image, game, coord){
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+50}, *game->get_img_size("more"), &Game::add_worker, "more_worker", game->get_img("more")));
    setting->add_button(new PushButton(game, {coord.x+156, coord.y+92}, *game->get_img_size("less"), &Game::remove_worker, "less_worker", game->get_img("less")));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+50}, {130, 30}, "Add a worker", game->get_color("increase_worker"), RECT, "add_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+92}, {130, 30}, "Pull a worker", game->get_color("decrease_worker"), RECT, "pull_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+133}, {150, 30}, "Nb worker: ", game->get_color("increase_worker"), RECT, "nb_worker"));
    setting->add_info_zone(new InfoZone(game, {coord.x+20, coord.y+175}, {150, 30}, "Nb max worker: ", game->get_color("decrease_worker"), RECT, "nb_max_worker"));
    setting->get_info_zone("nb_worker")->set_value(0.0);
}

Generator::~Generator(){}


void Generator::init_reverse(){
    Xy set_pos = setting->get_reverse()->get_pos();
    setting->get_reverse()->add_tab_info(new TabInfo(game, {5, 6}, {set_pos.x, set_pos.y+(game->get_size_setting_building()->y-30*6)}, {80, 30}, "advanced_stat"));
    TabInfo *t = setting->get_reverse()->get_tab_info("advanced_stat");
    t->set_base_text({0, 3}, "Nombre max\nde travailleur");
    t->set_base_text({0, 4}, "Ratio d'un \ntravailleur");
    t->set_base_text({0, 5}, "Ratio total \nmaximum");
    t->set_color({1, 4}, Qt::green);
    t->set_color({1, 5}, Qt::green);
    for(int i=0; i<lvl_max; i++){
        t->set_value({i+1, 4}, value_per_worker[i]);
        t->set_value({i+1, 5}, value_per_worker[i]*max_worker[i]);
    }
    nb_line = 6;
}

void Generator::init_personnal_value(){}