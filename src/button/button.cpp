#include "button.h"
#include "../Game.h"


PushButton::PushButton(Game *game, Xy pos, Xy size, void (Game::*f)(), std::string name, QPixmap *img) : GraphicsPixmapItem(img, game->get_view()->get_scene(), {pos.x+size.x/2, pos.y+size.y/2}){
    this->game = game;
    this->scene = game->get_view()->get_scene();
    this->size = size;
    this->name = name;
    this->click = f;
    this->pos = pos;
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
    if(size.x > 106 || size.y > 106){
        return coord->x < pos.x+size.x && coord->x+70 > pos.x && coord->y+70 < pos.y+size.y && coord->y+70 > pos.y;    
    }
    return coord->x < pos.x+size.x && coord->x > pos.x && coord->y < pos.y+size.y && coord->y > pos.y;
}

void PushButton::is_clicked(){
    std::cout << name << std::endl;
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