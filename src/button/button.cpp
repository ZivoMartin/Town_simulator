#include "button.h"
#include "../Game.h"


PushButton::PushButton(Game *game, Xy pos, Xy size, void (Game::*f)(), std::string name, QPixmap *img) : GraphicsPixmapItem(img, game->get_view()->get_scene(), pos){
    this->game = game;
    this->scene = game->get_view()->get_scene();
    this->size = size;
    this->name = name;
    this->click = f;
    set_pos(pos);
}

PushButton::~PushButton(){   
}

void PushButton::remove(){
    remove_img();
    game->erase_button(this);
}

void PushButton::add(){
    add_img();
    game->add_button(this);
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