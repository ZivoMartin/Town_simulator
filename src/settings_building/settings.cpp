#include "settings.h"
#include "../Game.h"

Setting::Setting(Game *game, Xy pos) : QGraphicsRectItem(pos.x, pos.y, game->get_size_setting()->x, game->get_size_setting()->y){
    this->game = game;
    this->origin = pos;
    this->scene = game->get_view()->get_scene(); 
    this->size = {game->get_size_setting()->x, game->get_size_setting()->y};
    this->close_button = new PushButton(game, "X", pos, game->get_color("close_button"), {30, 30}, &Game::close_setting);    
    this->brush = new QBrush(game->get_color("settings"));
    setBrush(*brush);
}

Setting::~Setting(){
    delete brush;
    delete close_button;
}

void Setting::close(){
    scene->removeItem(this);
    game->set_current_setting(nullptr);
    close_button->remove();
    for(unsigned int i=0; i<button_vec.size(); i++){
        button_vec[i]->remove();
    }
}

void Setting::open(){
    scene->addItem(this);
    close_button->add();
    for(unsigned int i=0; i<button_vec.size(); i++){
        button_vec[i]->add();
    }
}

void Setting::set_pos(Xy pos){
    setPos(pos.x - origin.x, pos.y - origin.y);
    close_button->set_pos(pos);
}

void Setting::add_button(PushButton *new_button){
    button_vec.push_back(new_button);
}

void Setting::erase_button(PushButton *button){
    for(unsigned int i=0; i<button_vec.size(); i++){
        if(button_vec[i] == button){
            button_vec.erase(button_vec.begin()+i);
            break;
        }
    }
}
