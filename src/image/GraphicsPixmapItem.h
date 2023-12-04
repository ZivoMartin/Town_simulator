#ifndef GraphicsPixmapItem_safe
#define GraphicsPixmapItem_safe
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include "../struct.h"


class GraphicsPixmapItem : QGraphicsPixmapItem{

public:
    GraphicsPixmapItem(QPixmap *image, QGraphicsScene *scene, Xy coord);
    ~GraphicsPixmapItem();
    Xy *get_pos();
    void set_pos_img(Xy coord);
    Xy get_img_size();

private:
    QGraphicsScene *scene;
    Xy position;
    QPixmap *image;
};

#endif