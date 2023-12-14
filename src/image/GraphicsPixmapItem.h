#ifndef GraphicsPixmapItem_safe
#define GraphicsPixmapItem_safe
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include "../struct.h"

class Game;

class GraphicsPixmapItem : QGraphicsPixmapItem{

public:
    GraphicsPixmapItem(QPixmap *image, QGraphicsScene *scene, Xy coord);
    ~GraphicsPixmapItem();
    Xy *get_pos();
    void set_pos_img(Xy coord);
    Xy get_img_size();
    void add_img();
    void remove_img();
    bool is_open();

private:
    QGraphicsScene *scene;
    Xy position;
    QPixmap *image;
    bool is_display = false;
};

#endif