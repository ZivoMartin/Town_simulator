#include "info_zone.h"
#include "../Game.h"

InfoZone::InfoZone(Game *game, Xy pos, Xy size, QString txt, QColor color, form_type type_bg, std::string name) : QGraphicsTextItem(txt){
    position = pos;
    size = size;
    scene = game->get_view()->get_scene();
    this->game = game;
    base_text = txt;
    bg = new GraphicBg(type_bg, pos, size, color, scene);
    if(type_bg == CIRCLE){
        this->setPos(pos.x+10, pos.y+size.y/3.6); 
    }else{
        this->setPos(pos.x+10, pos.y); 
    }
    this->setDefaultTextColor(QColor(0, 0, 0));
    this->name = name;
}

InfoZone::~InfoZone(){
    delete bg;
}

float InfoZone::get_value(){
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
    if(bg->get_type() == CIRCLE){
        this->setPos(pos.x+10, pos.y+size.y/3.6); 
    }else{
        this->setPos(pos.x+10, pos.y); 
    }
    bg->set_pos(pos); 
}

std::string InfoZone::get_name(){
    return name;
}

Xy InfoZone::get_pos(){
    return position;
}