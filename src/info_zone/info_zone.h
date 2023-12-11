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
    void set_base_text(QString new_base_text);
    void decal_txt(Xy decal);

private:
    Xy text_position;
    Xy bg_position;
    Xy size;
    Xy decal = {0, 0};
    float value = 0.0;
    QString base_text;
    Game *game;
    GraphicBg *bg;
    QGraphicsScene *scene;
    std::string name;
};

#endif