#ifndef safe_info_zone
#define safe_info_zone
#include <QString>
#include <iostream>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QColor>
#include "../struct.h"

class Game;

class InfoZone : public QGraphicsEllipseItem{

public:
    InfoZone(Game *game, Xy pos, Xy size, QString txt, QColor color, float base_value);
    ~InfoZone();
    void set_value(float x);
    int get_value();

private:
    Xy position;
    Xy size;
    int value;
    QString base_text;
    Game *game;
    QGraphicsTextItem *text_item;
    QBrush *brush;
};

#endif