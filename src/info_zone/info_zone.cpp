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
    free_map(&son_map);
}

void InfoZone::set_color(QColor color){
    bg->set_color(color);
}

float InfoZone::get_value(){
    return value;
}

void InfoZone::set_base_text(QString new_base_text){
    this->base_text = new_base_text;
    QString new_display = base_text;
    if(value_exist){
        new_display.append(QString::number(value));
    }
    this->setPlainText(new_display);
}

void InfoZone::set_value(float x){
    value_exist = true;
    value = x;
    QString new_display = base_text;
    new_display.append(QString::number(value));
    this->setPlainText(new_display);
}

void InfoZone::add(){
    bg->add();
    scene->addItem(this);
    is_open = true;
    for(auto el: son_map){
        son_map[el.first]->add();
    }
}

void InfoZone::remove(){
    bg->remove();
    scene->removeItem(this);
    is_open = false;
    for(auto el: son_map){
        son_map[el.first]->remove();
    }
}

void InfoZone::set_pos(Xy pos){
    if(bg->get_type() == CIRCLE){
        this->text_position = {pos.x+10, static_cast<int>(pos.y+size.y/3.6)}; 
    }else if(bg->get_type() == RECT){
        this->text_position = {pos.x+10, pos.y}; 
    }else{
        this->text_position = pos; 
    }
    for(auto el: son_map){
        Xy w_pos = son_map[el.first]->get_pos();
        son_map[el.first]->set_pos({pos.x + (w_pos.x-bg_position.x), pos.y + (w_pos.y-bg_position.y)}); 
    }
    this->setPos(text_position.x, text_position.y);
    bg->set_pos(pos); 
    bg_position = pos;
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

void InfoZone::set_text_color(QColor c){
    this->setDefaultTextColor(c);
}

void InfoZone::add_son(InfoZone *new_inf){
    new_inf->set_pos({bg_position.x+new_inf->get_pos().x, bg_position.y+new_inf->get_pos().y});
    son_map[new_inf->get_name()] = new_inf;
    if(is_open){
        new_inf->add();
    }
}   

float InfoZone::get_value_of_a_son(std::string name){
    return son_map[name]->get_value();
}

void InfoZone::set_base_text_of_a_son(QString new_txt, std::string name){
    son_map[name]->set_base_text(new_txt);
}

void InfoZone::set_value_of_a_son(float x, std::string name){
    son_map[name]->set_value(x);
}