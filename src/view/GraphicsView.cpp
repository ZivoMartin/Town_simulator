#include "GraphicsView.h"
#include "../Game.h"

GraphicsView::GraphicsView() : QGraphicsView(){
    this->scene = new QGraphicsScene();
    setMouseTracking(true);
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

void GraphicsView::mousePressEvent(QMouseEvent* event){
    Xy coord_clic = convert(mapToScene(event->pos()));
    if(event->button() == 1){
        game->screen_clicked(coord_clic);
    }else if(event->button() == 2){ 
    }   
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event){
    game->mouse_move(convert(mapToScene(event->pos())));
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event){
    game->click_release(convert(mapToScene(event->pos())));
}

Xy GraphicsView::convert(QPointF coord_clic){
    return {static_cast<int>(coord_clic.rx()), static_cast<int>(coord_clic.ry())};
}