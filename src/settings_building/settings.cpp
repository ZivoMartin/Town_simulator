#include "settings.h"
#include "../Game.h"


Setting::Setting(Game *game, Xy pos) : QGraphicsRectItem(pos.x, pos.y, game->get_size_setting()->x, game->get_size_setting()->y){
    game = game;
    size = {game->get_size_setting()->x, game->get_size_setting()->y};
    close_button = new PushButton("X", pos, game->get_color("close_button"), {30, 30});    
    brush = new QBrush(game->get_color("settings"));
    setBrush(*brush);
    QObject::connect(close_button, &QPushButton::released, this, &Setting::close);
}

Setting::~Setting(){
}

void Setting::close(){
    game->get_view()->get_scene()->removeItem(this);
    close_button->remove();
}

void Setting::open(){
    game->get_view()->get_scene()->addItem(this);
    close_button->add();
}