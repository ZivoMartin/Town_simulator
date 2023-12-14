#include "GraphicsPixmapItem.h"

GraphicsPixmapItem::GraphicsPixmapItem(QPixmap *image, QGraphicsScene *scene, Xy coord) : QGraphicsPixmapItem(*image){
    this->image = image;
    set_pos_img(coord);
    this->scene = scene;
}

GraphicsPixmapItem::~GraphicsPixmapItem(){   
    if(is_display){
        scene->removeItem(this);
    }
}

void GraphicsPixmapItem::set_pos_img(Xy pos){
    Xy s = get_img_size();
    this->position = pos;
    this->setPos(pos.x-s.x/2, pos.y-s.x/2);
}

Xy *GraphicsPixmapItem::get_pos(){
    return &position;
}

Xy GraphicsPixmapItem::get_img_size(){
    return {static_cast<int>(image->size().width()), static_cast<int>(image->size().width())};
}

void GraphicsPixmapItem::remove_img(){
    scene->removeItem(this);
    is_display = false;
}

void GraphicsPixmapItem::add_img(){
    scene->addItem(this);
    is_display = true;
}

bool GraphicsPixmapItem::is_open(){
    return is_display;
}