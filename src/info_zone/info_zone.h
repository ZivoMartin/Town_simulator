#ifndef safe_info_zone
#define safe_info_zone
#include <QString>
#include <iostream>
#include <QGraphicsTextItem>
#include <QColor>
#include "graphic_bg.h"
#include "../struct.h"

class Game;

class InfoZone : public QGraphicsTextItem{

public:
    InfoZone(Game *game, Xy pos, Xy size, QString txt, QColor color, float base_value, form_type type_bg);
    ~InfoZone();
    void set_value(float x);
    int get_value();
    void add();
    void remove();
    void set_pos(Xy pos);

private:
    Xy position;
    Xy size;
    int value;
    QString base_text;
    Game *game;
    GraphicBg *bg;
    QGraphicsScene *scene;
};

#endif