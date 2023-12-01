#ifndef GraphicsView_safe
#define GraphicsView_safe
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>

class Game;

class GraphicsView : public QGraphicsView{

public:
    GraphicsView();
    ~GraphicsView();
    QGraphicsScene * get_scene();
    void set_game(Game *game);
    
private:
    QGraphicsScene *scene;
    Game *game;
};

#endif