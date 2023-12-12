#include "graphic_bg.h"

GraphicBg::GraphicBg(form_type type, Xy pos, Xy size, QColor color, QGraphicsScene *scene){
    bg_union.type = type;
    brush = new QBrush(color);
    this->scene = scene;
    if(type == RECT){
        bg_union.bg.rect = new QGraphicsRectItem(0, 0, size.x, size.y);
        bg_union.bg.rect->setPos(pos.x, pos.y);
        bg_union.bg.rect->setBrush(*brush);
    }else if(type == CIRCLE){
        bg_union.bg.circle = new QGraphicsEllipseItem(0, 0, size.x, size.y);
        bg_union.bg.circle->setPos(pos.x, pos.y);
        bg_union.bg.circle->setBrush(*brush);
    }   
    this->size = size;
    this->pos = pos;
}

GraphicBg::~GraphicBg(){
    if(bg_union.type == RECT){
        delete bg_union.bg.rect;
    }else if(bg_union.type == CIRCLE){
        delete bg_union.bg.circle;
    }
    delete brush;
}

void GraphicBg::add(){
    if(bg_union.type == RECT){
        scene->addItem(bg_union.bg.rect);
    }else if(bg_union.type == CIRCLE){
        scene->addItem(bg_union.bg.circle);
    }
}

void GraphicBg::remove(){
    if(bg_union.type == RECT){
        scene->removeItem(bg_union.bg.rect);
    }else if(bg_union.type == CIRCLE){
        scene->removeItem(bg_union.bg.circle);
    }
}

void GraphicBg::set_pos(Xy pos){
    this->pos = pos;
    if(bg_union.type == RECT){
        bg_union.bg.rect->setPos(pos.x, pos.y);
    }else if(bg_union.type == CIRCLE){
        bg_union.bg.circle->setPos(pos.x, pos.y);
    } 
}

form_type GraphicBg::get_type(){
    return bg_union.type;
}