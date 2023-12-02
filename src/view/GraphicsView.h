#ifndef GraphicsView_safe
#define GraphicsView_safe
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <QColor>
#include "../struct.h"
class Game;

class GraphicsView : public QGraphicsView{

public:
    GraphicsView();
    ~GraphicsView();
    QGraphicsScene * get_scene();
    void set_game(Game *game);
    void set_bg_color(QColor *color);
    void zoom(double factor);
    void set_size(Xy s);
    
    
private:
    QGraphicsScene *scene;
    Game *game;
};

#endif