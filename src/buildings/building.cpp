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
    setting = new Setting(game, coord, *game->get_size_setting_building(), nullptr);
    setting->set_reverse_button();
    setting->add_button(new PushButton(game, {coord.x+320, coord.y+160}, *game->get_img_size("been"), &Game::sold_building, "been", game->get_img("been")));
    setting->add_button(new PushButton(game, {coord.x+255, coord.y+160}, *game->get_img_size("lvl_up"), &Game::lvl_up, "lvl_up", game->get_img("lvl_up")));
    setting->add_info_zone(new InfoZone(game, {coord.x+255, coord.y+190}, {40, 30}, "$", game->get_color("upgrade_price"), RECT, "upgrade_price"));
    setting->add_info_zone(new InfoZone(game, {coord.x+320, coord.y+190}, {40, 30}, "$", game->get_color("sold_price"), RECT, "sold_price"));
    setting->add_info_zone(new InfoZone(game, {coord.x+245, coord.y+10}, {120, 30}, "", game->get_color("lvl_info"), RECT, "lvl"));
    setting->get_info_zone("lvl")->set_value(1);
    setting->get_info_zone("upgrade_price")->decal_txt({-10, 0});
    setting->get_info_zone("sold_price")->decal_txt({-10, 0});
}

int Building::get_nb_worker(){
    return nb_worker;
}

void Building::lvl_up(){
    lvl += 1;
    setting->get_info_zone("lvl")->set_value(lvl+1);
    setting->get_info_zone("upgrade_price")->set_value(price_to_up[lvl]);
    setting->get_info_zone("nb_max_worker")->set_value(max_worker[lvl]);
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
}