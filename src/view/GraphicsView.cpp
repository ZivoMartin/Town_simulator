#include "GraphicsView.h"
#include "../Game.h"

GraphicsView::GraphicsView() : QGraphicsView(){
    this->scene = new QGraphicsScene();
    setScene(scene);
}

GraphicsView::~GraphicsView(){
    delete scene;
}

QGraphicsScene * GraphicsView::get_scene(){
    return scene;
}

void GraphicsView::set_game(Game *game){
    this->game = game;
}
void GraphicsView::set_bg_color(QColor *color){
    QBrush brush(*color);
    scene->setBackgroundBrush(brush);
}

void GraphicsView::zoom(double factor){
    setTransform(transform().scale(1.0/factor, 1.0/factor));
}

void GraphicsView::set_size(Xy s){
    scene->setSceneRect(0, 0, s.x, s.y);
}

