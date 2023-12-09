#include "building.h"
#include "../Game.h"
#include "../settings_building/settings.h"

Building::Building(QPixmap *image, Game *game, Xy coord) : GraphicsPixmapItem(image, game->get_view()->get_scene(), coord){
    origin_pos = coord;
    this->game = game;
    setting = new Setting(game, coord, *game->get_size_setting_building());
    this->add_img();
}

Building::~Building(){
    if(setting_union != nullptr){
        delete setting_union;
    }
}

int Building::get_nb_worker(){
    return nb_worker;
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
    return value_per_worker*nb_worker;
}

void Building::clicked(){
    game->set_current_setting(setting, setting_union);
}

Xy *Building::get_current_pos(){
    return get_pos();
}