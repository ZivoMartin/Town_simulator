#ifndef safe_info_zone
#define safe_info_zone
#include <QString>
#include <iostream>
#include <QGraphicsTextItem>
#include <QColor>
#include "graphic_bg.h"

class Game;

class InfoZone : public QGraphicsTextItem{

public:
    InfoZone(Game *game, Xy pos, Xy size, QString txt, QColor color, form_type type_bg, std::string name);
    ~InfoZone();
    void set_value(float x);
    float get_value();
    void add();
    void remove();
    void set_pos(Xy pos);
    Xy get_pos();
    std::string get_name();

private:
    Xy position;
    Xy size;
    float value;
    QString base_text;
    Game *game;
    GraphicBg *bg;
    QGraphicsScene *scene;
    std::string name;
};

#endif