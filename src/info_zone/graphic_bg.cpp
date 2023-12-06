#include "graphic_bg.h"

GraphicBg::GraphicBg(form_type type, Xy pos, Xy size, QColor color, QGraphicsScene *scene){
    bg_union.type = type;
    brush = new QBrush(color);
    this->scene = scene;
    if(type == RECT){
        bg_union.bg.rect = new QGraphicsRectItem(pos.x, pos.y, size.x, size.y);
        bg_union.bg.rect->setBrush(*brush);
        scene->addItem(bg_union.bg.rect);
    }else{
        bg_union.bg.circle = new QGraphicsEllipseItem(pos.x, pos.y, size.x, size.y);
        bg_union.bg.circle->setBrush(*brush);
        scene->addItem(bg_union.bg.circle);
    }   
    this->size = size;
    this->pos = pos;
    this->origin = pos;
}

GraphicBg::~GraphicBg(){
    if(bg_union.type == RECT){
        delete bg_union.bg.rect;
    }else{
        delete bg_union.bg.circle;
    }
    delete brush;
}

void GraphicBg::add(){
    if(bg_union.type == RECT){
        scene->addItem(bg_union.bg.rect);
    }else{
        scene->addItem(bg_union.bg.circle);
    }
}

void GraphicBg::remove(){
    if(bg_union.type == RECT){
        scene->removeItem(bg_union.bg.rect);
    }else{
        scene->removeItem(bg_union.bg.circle);
    }
}

void GraphicBg::set_pos(Xy pos){
    this->pos = pos;
    if(bg_union.type == RECT){
        bg_union.bg.rect->setPos(pos.x-origin.x, pos.y-origin.y);
    }else{
        bg_union.bg.circle->setPos(pos.x-origin.x, pos.y-origin.y);
    } 
}