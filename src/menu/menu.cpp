#include "menu.h"
#include "../Game.h"

Menu::Menu(Game *game){
    this->game = game;
    Xy *screen_size = game->get_screen_size();
    start_game_button = new PushButton(game, {static_cast<int>(screen_size->x*0.4), static_cast<int>(screen_size->y*0.5)}, *game->get_img_size("start"), &Game::start_signal, "start_game", game->get_img("start"));
    start_game_button->add();
    wait();
}

Menu::~Menu(){

}

void Menu::return_to_menu(){
    game->reset();
    start_game_button->add();
    game_is_starting = false;
    wait();
}

void Menu::wait(){
    QTimer::singleShot(20, game, [=](){
        game->get_view()->update();
        if(game_is_starting){
            game->start();    
        }else{
            wait();
        }
    });
}

void Menu::start_game(){
    start_game_button->remove();
    game_is_starting = true;
}

bool Menu::get_activity(){
    return !game_is_starting;
}