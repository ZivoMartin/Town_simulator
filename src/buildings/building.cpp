#include "building.h"

Building::Building(QPixmap *image, QGraphicsScene *scene, Xy coord) : GraphicsPixmapItem(image, scene, coord){
    origin_pos = coord;
}

Building::~Building(){}

void Building::set_worker(int x){
    nb_worker += x;
}

int Building::get_nb_worker(){
    return nb_worker;
}

int Building::get_level(){
    return lvl;
}

void Building::level_up(){
    lvl += 1;
}

void Building::drag(Xy new_pos){
    set_pos_img(new_pos);
}

Xy *Building::get_origin_pos(){
    return &origin_pos;
}

void Building::set_origin_pos(Xy new_pos){
    origin_pos = new_pos;
    set_pos_img(new_pos);
}

Xy Building::get_size(){
    return get_img_size();
}

int Building::get_efficiency(){
    return value_per_worker*nb_worker;
}