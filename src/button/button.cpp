#include "button.h"
#include "../Game.h"


PushButton::PushButton(Game *game, QString txt, Xy pos, QColor color, Xy size, void (Game::*f)()) : QGraphicsRectItem(pos.x, pos.y, size.x, size.y){
    this->game = game;
    this->scene = game->get_view()->get_scene();
    this->size = size;
    this->origin_pos = pos;
    this->pos = pos;
    brush = new QBrush(color);
    this->setBrush(*brush);

    base_text = txt;
    this->text_item = new QGraphicsTextItem(txt);
    text_item->setPos(pos.x+3, pos.y); 
    text_item->setDefaultTextColor(QColor(0, 0, 0));

    this->click = f;
}

PushButton::~PushButton(){
    delete brush;
    delete text_item;
}

void PushButton::remove(){
    this->scene->removeItem(text_item);
    this->scene->removeItem(this);
    game->erase_button(this);
}

void PushButton::add(){
    this->scene->addItem(this);
    this->scene->addItem(text_item);
    game->add_button(this);
}

bool PushButton::is_it(Xy *coord){
    return coord->x < pos.x+size.x && coord->x > pos.x && coord->y < pos.y+size.y && coord->y > pos.y;
}

void PushButton::is_clicked(){
    (game->*(click))();
}

void PushButton::set_pos(Xy coord){
    setPos(coord.x - origin_pos.x, coord.y - origin_pos.y);
    this->pos = coord;
    text_item->setPos(coord.x, coord.y);
}