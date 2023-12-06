#ifndef safe_setting
#define safe_setting

#include <iostream>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QApplication>

#include "../buildings/field.h"
#include "../buildings/house.h"
#include "../buildings/shop.h"
#include "../struct.h"
#include "../button/button.h"


class Setting: public QGraphicsRectItem{

public:    
    Setting(Game *game, Xy pos);
    ~Setting();
    void open();
    void close();
    void set_pos(Xy pos);
    void add_button(PushButton *button);
    void erase_button(PushButton *button);


private:
    PushButton *close_button;
    Xy size;
    Game *game;
    QBrush *brush;
    QGraphicsScene *scene;
    Xy origin;
    std::vector<PushButton*> button_vec;
};

#endif