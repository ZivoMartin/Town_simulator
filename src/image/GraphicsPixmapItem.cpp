#include "GraphicsPixmapItem.h"

GraphicsPixmapItem::GraphicsPixmapItem(QPixmap *image, QGraphicsScene *scene, Xy coord) : QGraphicsPixmapItem(*image){
    this->image = image;
    set_pos_img(coord);
    this->position = coord;
    scene->addItem(this);
    this->scene = scene;
}

GraphicsPixmapItem::~GraphicsPixmapItem(){   
    scene->removeItem(this);
}

void GraphicsPixmapItem::set_pos_img(Xy pos){
    position = pos;
    this->setPos(pos.x, pos.y);
}



Xy *GraphicsPixmapItem::get_pos(){
    return &position;
}

Xy GraphicsPixmapItem::get_size(){
    return {static_cast<int>(image->size().width()), static_cast<int>(image->size().width())};
}