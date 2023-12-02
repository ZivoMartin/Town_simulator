#include "building.h"

Building::Building(QPixmap *image, QGraphicsScene *scene, Xy coord) : GraphicsPixmapItem(image, scene, coord){}

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