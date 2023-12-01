#include "Game.h"




Game::Game(GraphicsView *view): QMainWindow(){
    view->set_game(this);
    this->view = view;
}

Game::~Game(){
    delete view;
}

int Game::get_iter(){
    return iter;
}




int random(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> random_nbr(min, max);
    return(random_nbr(generator));
}


int get_dist(Xy *coord1, Xy *coord2){
    return (coord1->x-coord2->x)*(coord1->x-coord2->x) + (coord1->y-coord2->y)*(coord1->y-coord2->y);
}