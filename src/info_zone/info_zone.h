#ifndef safe_info_zone
#define safe_info_zone
#include <QString>
#include <iostream>
#include <QGraphicsTextItem>
#include <QColor>
#include "graphic_bg.h"
#include "../common_functions/common_functions.h"

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
    void set_text_color(QColor c);
    void add_son(InfoZone *new_inf);
    float get_value_of_a_son(std::string name);
    void set_base_text_of_a_son(QString new_txt, std::string name);
    void set_value_of_a_son(float x, std::string name);

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
    std::map<std::string, InfoZone *> son_map; 
    bool is_open = false;
};

#endif