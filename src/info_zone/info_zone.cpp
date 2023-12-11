#include "info_zone.h"
#include "../Game.h"

InfoZone::InfoZone(Game *game, Xy pos, Xy size, QString txt, QColor color, form_type type_bg, std::string name) : QGraphicsTextItem(txt){
    this->bg_position = pos;
    size = size;
    scene = game->get_view()->get_scene();
    this->game = game;
    base_text = txt;
    bg = new GraphicBg(type_bg, pos, size, color, scene);
    if(type_bg == CIRCLE){
        this->text_position = {pos.x+10, static_cast<int>(pos.y+size.y/3.6)}; 
    }else{
        this->text_position = {pos.x+10, pos.y}; 
    }
    this->setPos(text_position.x, text_position.y); 
    this->setDefaultTextColor(QColor(0, 0, 0));
    this->name = name;
}

InfoZone::~InfoZone(){
    delete bg;
}

float InfoZone::get_value(){
    return value;
}

void InfoZone::set_base_text(QString new_base_text){
    this->base_text = new_base_text;
    set_value(value);
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
    if(bg->get_type() == CIRCLE){
        this->text_position = {pos.x+10, static_cast<int>(pos.y+size.y/3.6)}; 
    }else{
        this->text_position = {pos.x+10, pos.y}; 
    }
    this->setPos(text_position.x, text_position.y);
    bg->set_pos(pos); 
    decal_txt(decal);
}

std::string InfoZone::get_name(){
    return name;
}

Xy InfoZone::get_pos(){
    return bg_position;
}

void InfoZone::decal_txt(Xy decal){
    this->decal = decal;
    this->setPos(text_position.x + decal.x, text_position.y+decal.y);
}