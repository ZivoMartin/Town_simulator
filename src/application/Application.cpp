#include "Application.h"

Application::Application(int argc, char **argv) : QApplication(argc, argv){}

Application::~Application(){}

void Application::set_game(Game *game){
    this->game = game;
}