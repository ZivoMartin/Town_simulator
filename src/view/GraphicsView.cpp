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
