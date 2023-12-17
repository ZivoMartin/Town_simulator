#include  "loading_bar.h"
#include "../Game.h"

LoadingBar::LoadingBar(Game *game, Xy pos, Xy size, void (Game::*f)(), QString txt) : QGraphicsRectItem(pos.x, pos.y, size.x, size.y){
    this->game = game;
    this->pos = pos;
    this->size = size;
    this->achievement = f;
    this->scene = game->get_view()->get_scene();
    this->load_bar_brush = new QBrush(Qt::green);
    this->bar = new QGraphicsRectItem(pos.x, pos.y, 2, size.y);
    this->bar->setBrush(*load_bar_brush);
    this->txt = new InfoZone(game, pos, size, txt, QColor(255, 255, 255), WITHOUT, "text");
    this->txt->decal_txt({size.x/45, size.y/6});
}

LoadingBar::~LoadingBar(){
    if(is_open){
        remove();
    }
    delete load_bar_brush;
    delete txt;
    delete bar;
}

void LoadingBar::load(){
    QTimer::singleShot(20, game, [=](){
        state += ratio/5;
        bar->setRect(pos.x, pos.y, state, size.y);
        if(state >= size.x){
            (game->*(achievement))();
            state = 0;
        }else if(!stop){
            load();
        }else{
            stop = false;
        }
    });
}

void LoadingBar::stop_load(){
    stop = true;
}

void LoadingBar::set_ratio(int percent_value){
    if(percent_value > 100){
        percent_value = 100;
    }
    ratio = (percent_value*size.x)/100;
}


void LoadingBar::add(){
    scene->addItem(this);
    scene->addItem(bar);
    txt->add();
    is_open = true;
}

void LoadingBar::remove(){
    scene->removeItem(this);
    scene->removeItem(bar);
    txt->remove();
    is_open = false;
}