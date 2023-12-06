#ifndef safe_button
#define safe_button

#include <QPushButton>
#include <iostream>
#include <QGraphicsScene>
#include <QString>
#include <QColor>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsTextItem>
#include "../struct.h"

class Game;

class PushButton: public QGraphicsRectItem{

public:
    PushButton(Game *game, QString txt, Xy pos, QColor color, Xy size, void (Game::*f)());
    ~PushButton();
    void add();
    void remove();
    void is_clicked();
    bool is_it(Xy *coord);
    void set_pos(Xy coord);

private:
    Game *game;
    QGraphicsScene *scene;
    Xy size;
    Xy pos;
    void (Game::*click)();
    QBrush *brush;
    QString base_text;
    QGraphicsTextItem *text_item;
    Xy origin_pos;
    std::string name;
};

#endif