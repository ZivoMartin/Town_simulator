#include "button.h"
#include "../Game.h"


PushButton::PushButton(Game *game, Xy pos, Xy size, void (Game::*f)(), std::string name, QPixmap *img) : GraphicsPixmapItem(img, game->get_view()->get_scene(), {pos.x+size.x/2, pos.y+size.y/2}){
    this->game = game;
    this->scene = game->get_view()->get_scene();
    this->size = size;
    this->name = name;
    this->click = f;
    this->pos = pos;
    this->pos.y -= (size.x/200)*75;
}

PushButton::~PushButton(){
    if(info_zone != nullptr){
        delete info_zone;
    }   
}

void PushButton::remove(){
    remove_img();
    game->erase_button(this);
    is_display = false;
    if(info_zone != nullptr){
        info_zone->remove();
    }
}

void PushButton::add(){
    add_img();
    game->add_button(this);
    is_display = true;
    if(info_zone != nullptr){
        info_zone->add();
    }
}

bool PushButton::is_it(Xy *coord){
    return coord->x < pos.x+size.x && coord->x > pos.x && coord->y < pos.y+size.y && coord->y > pos.y;
}

void PushButton::is_clicked(){
    (game->*(click))();
}

void PushButton::set_pos(Xy coord){
    set_pos_img({coord.x+size.x/2, coord.y+size.y/2});
    this->pos = coord;
}

Xy PushButton::get_pos(){
    return pos;
}

std::string PushButton::get_name(){
    return name;
}

void PushButton::set_freezable(){
    freezable = true;
}

bool PushButton::get_freezable(){
    return freezable;
}

void PushButton::set_info_zone(QString txt){
    this->info_zone = new InfoZone(game, {pos.x, pos.y}, size, txt, QColor(150, 150, 150), RECT, "txt");
    info_zone->decal_txt({size.x/10, 10});
    info_zone->set_txt_size(size.y/2);
}