#include "info_zone.h"
#include "../Game.h"

InfoZone::InfoZone(Game *game, Xy pos, Xy size, QString txt, QColor color, float base_value) : QGraphicsEllipseItem(pos.x, pos.y, size.x, size.y){
    position = pos;
    size = size;
    game = game;
    base_text = txt;
    text_item = new QGraphicsTextItem(txt);
    this->brush = new QBrush(color);
    this->setBrush(*brush);
    text_item->setPos(pos.x+10, pos.y + size.y/4.5); 
    text_item->setDefaultTextColor(QColor(0, 0, 0));
    game->get_view()->get_scene()->addItem(this);
    game->get_view()->get_scene()->addItem(text_item);
    set_value(base_value);
}

InfoZone::~InfoZone(){
    delete text_item;
    delete brush;
}

int InfoZone::get_value(){
    return value;
}

void InfoZone::set_value(float x){
    value = x;
    QString new_display = base_text;
    new_display.append(QString::number(value));
    text_item->setPlainText(new_display);
}