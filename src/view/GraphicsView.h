#ifndef GraphicsView_safe
#define GraphicsView_safe
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <QColor>
#include <QMouseEvent>
#include <QPointF>

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
    void mousePressEvent(QMouseEvent* event) override; 
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    Xy convert(QPointF coord_clic);   
    
private:
    QGraphicsScene *scene;
    Game *game;
};

#endif