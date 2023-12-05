#ifndef safe_setting
#define safe_setting

#include <iostream>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QObject>
#include "../buildings/field.h"
#include "../buildings/house.h"
#include "../buildings/shop.h"
#include "../struct.h"
#include "../button/button.h"

class Game;

class Setting: public QGraphicsRectItem, public QObject{
    
public:    
    Setting(Game *game, Xy pos);
    ~Setting();
    void open();

public slots:
     void close();

private:
    PushButton *close_button;
    Xy size;
    Game *game;
    QBrush *brush;
};

#endif