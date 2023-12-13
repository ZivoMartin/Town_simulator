#include "building.h"
#include "../Game.h"
#include "../settings_building/settings.h"

Building::Building(QPixmap *image, Game *game, Xy coord) : GraphicsPixmapItem(image, game->get_view()->get_scene(), coord){
    origin_pos = coord;
    this->game = game;
    init_setting(coord);
    this->add_img();
}

Building::~Building(){
    if(setting_union != nullptr){
        delete setting_union;
    }
    delete setting;
    Xy s = get_size();
    game->erase_zone(&origin_pos, &s);

}

void Building::init_setting(Xy coord){
    Xy *set_s = game->get_size_setting_building();
    setting = new Setting(game, coord, *set_s, nullptr);
    setting->set_reverse_button();
    setting->add_button(new PushButton(game, {coord.x+320, coord.y+160}, *game->get_img_size("been"), &Game::sold_building, "been", game->get_img("been")));
    setting->add_button(new PushButton(game, {coord.x+255, coord.y+160}, *game->get_img_size("lvl_up"), &Game::lvl_up, "lvl_up", game->get_img("lvl_up")));
    setting->add_info_zone(new InfoZone(game, {coord.x+255, coord.y+190}, {40, 30}, "$", game->get_color("upgrade_price"), RECT, "upgrade_price"));
    setting->add_info_zone(new InfoZone(game, {coord.x+320, coord.y+190}, {40, 30}, "$", game->get_color("sold_price"), RECT, "sold_price"));
    setting->add_info_zone(new InfoZone(game, {coord.x+245, coord.y+10}, {120, 30}, "", game->get_color("lvl_info"), RECT, "lvl"));
    setting->get_info_zone("lvl")->set_value(1);
    setting->get_info_zone("upgrade_price")->decal_txt({-10, 0});
    setting->get_info_zone("sold_price")->decal_txt({-10, 0});
    setting->get_reverse()->add_info_zone(new InfoZone(game, {static_cast<int>(coord.x+set_s->x*0.35), coord.y+10}, {120, 30}, "", game->get_color("reverse_info_color"), RECT, "header"));
}

void Building::init_reverse_for_efficient_building(){
    Xy set_pos = setting->get_reverse()->get_pos();
    setting->get_reverse()->add_tab_info(new TabInfo(game, {5, 6}, {set_pos.x, set_pos.y+(game->get_size_setting_building()->y-30*6)}, {80, 30}, "advanced_stat"));
    TabInfo *t = setting->get_reverse()->get_tab_info("advanced_stat");
    t->set_base_text({0, 3}, "Nombre maximum de travailleur");
    t->set_base_text({0, 4}, "Ratio d'un travailleur");
    t->set_base_text({0, 5}, "Ratio total maximum");
    t->set_color({1, 4}, Qt::green);
    t->set_color({1, 5}, Qt::green);
    for(int i=0; i<lvl_max; i++){
        t->set_value({i+1, 4}, value_per_worker[i]);
        t->set_value({i+1, 5}, value_per_worker[i]*max_worker[i]);
    }
    nb_line = 6;
}

void Building::init_reverse_for_house(){
    Xy set_pos = setting->get_reverse()->get_pos();
    setting->get_reverse()->add_tab_info(new TabInfo(game, {5, 4}, {set_pos.x, set_pos.y+(game->get_size_setting_building()->y-30*6)}, {80, 30}, "advanced_stat"));
    setting->get_reverse()->get_tab_info("advanced_stat")->set_base_text({0, 3}, "Nombre maximum d'habitant'");
    nb_line = 4;
}

int Building::get_nb_worker(){
    return nb_worker;
}

void Building::lvl_up(){
    lvl += 1;
    setting->get_info_zone("lvl")->set_value(lvl+1);
    setting->get_info_zone("upgrade_price")->set_value(price_to_up[lvl]);
    setting->get_info_zone("nb_max_worker")->set_value(max_worker[lvl]);
    TabInfo *t = setting->get_reverse()->get_tab_info("advanced_stat");
    for(int i = 0; i<nb_line; i++){
        t->set_color({lvl, i}, game->get_color("reverse_info_color"));
        t->set_color({lvl+1, i}, Qt::green);
    }
}

int Building::get_level(){
    return lvl;
}

void Building::drag(Xy new_pos){
    set_pos_img(new_pos);
}

Xy *Building::get_origin_pos(){
    return &origin_pos;
}

void Building::set_origin_pos(Xy new_pos){
    origin_pos = new_pos;
    set_pos_img(new_pos);
    setting->set_pos(new_pos);
}

Xy Building::get_size(){
    return get_img_size();
}

float Building::get_efficiency(){
    return nb_worker*value_per_worker[lvl];
}

int Building::get_price_to_up(){
    return price_to_up[lvl];
}


void Building::clicked(){
    game->set_current_setting(setting, setting_union);
}

Xy *Building::get_current_pos(){
    return get_pos();
}

void Building::sold(){
    game->increase_gold(value_for_sold[lvl]);
    game->kik_workers(nb_worker);
    delete this;
}

void Building::init_common_value(){
    setting->get_info_zone("nb_max_worker")->set_value(static_cast<float>(max_worker[0]));
    setting->get_info_zone("sold_price")->set_value(value_for_sold[0]);
    setting->get_info_zone("upgrade_price")->set_value(price_to_up[0]);
    setting->get_reverse()->get_info_zone("header")->decal_txt({25, 0});
    TabInfo *t = setting->get_reverse()->get_tab_info("advanced_stat");
    for(int i = 1; i<5; i++){
        t->set_base_text({i, 0}, "niveau ");
        t->set_value({i, 0}, i);
    }
    t->set_color({1, 0}, Qt::green);
    t->set_color({1, 1}, Qt::green);
    t->set_color({1, 2}, Qt::green);
    t->set_color({1, 3}, Qt::green);
    t->set_base_text({0, 1}, "Coût d'amelioration");
    t->set_base_text({0, 2}, "Gain de vente");
    for(int i=0; i<lvl_max; i++){
        if (i != lvl_max-1) {
            t->set_value({i+1, 1}, price_to_up[i]);
        }else{
            t->set_base_text({i+1, 1}, "-");
        }
        t->set_value({i+1, 2}, value_for_sold[i]);
        t->set_value({i+1, 3}, max_worker[i]);
    }
}