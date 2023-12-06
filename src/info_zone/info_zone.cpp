#include "info_zone.h"
#include "../Game.h"

InfoZone::InfoZone(Game *game, Xy pos, Xy size, QString txt, QColor color, form_type type_bg) : QGraphicsTextItem(txt){
    position = pos;
    size = size;
    scene = game->get_view()->get_scene();
    this->game = game;
    base_text = txt;
    bg = new GraphicBg(type_bg, pos, size, color, scene);
    this->setPos(pos.x+10, pos.y + size.y/4.5); 
    this->setDefaultTextColor(QColor(0, 0, 0));
    scene->addItem(this);
}

InfoZone::~InfoZone(){
    delete bg;
}

int InfoZone::get_value(){
    return value;
}

void InfoZone::set_value(float x){
    value = x;
    QString new_display = base_text;
    new_display.append(QString::number(value));
    this->setPlainText(new_display);
}

void InfoZone::add(){
    bg->add();
    scene->addItem(this);
}

void InfoZone::remove(){
    bg->remove();
    scene->removeItem(this);
}

void InfoZone::set_pos(Xy pos){
    this->position = pos;
    this->setPos(pos.x+10, pos.y + size.y/4.5);
    bg->set_pos(pos); 
}