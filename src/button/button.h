#ifndef safe_button
#define safe_button

#include <QPushButton>
#include <iostream>
#include <QGraphicsScene>
#include <QString>
#include <QColor>
#include <QBrush>
#include "../struct.h"
#include "../image/GraphicsPixmapItem.h"


class PushButton: public GraphicsPixmapItem{

public:
    PushButton(Game *game, Xy pos, Xy size, void (Game::*f)(), std::string name, QPixmap *img);
    ~PushButton();
    void add();
    void remove();
    void is_clicked();
    bool is_it(Xy *coord);
    void set_pos(Xy coord);
    std::string get_name();
    Xy get_pos();
    void set_freezable();
    bool get_freezable();

private:
    Game *game;
    QGraphicsScene *scene;
    Xy size;
    Xy pos;
    void (Game::*click)();
    QBrush *brush;
    QString base_text;
    QGraphicsTextItem *text_item;
    std::string name;
    bool freezable = false;
};

#endif