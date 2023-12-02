#include "Game.h"

Game::Game(GraphicsView *view): QMainWindow(){
    view->set_game(this);
    this->view = view;
    load_images();
    setup_scene();
}

Game::~Game(){
    for( auto & field: field_vec){
        delete field;
    }
    delete images_map["house"];
    delete images_map["field"];
    delete images_map["shop"];
    delete background_color;
    delete view;
}

int Game::get_iter(){
    return iter;
}

void Game::load_images(){
    images_map["house"] = new QPixmap();
    images_map["field"] = new QPixmap();
    images_map["shop"] = new QPixmap();
    
    images_map["house"]->load("../images/house.png");
    images_map["field"]->load("../images/field.png");
    images_map["shop"]->load("../images/shop.png");
    
    *images_map["house"] = images_map["house"]->scaled(100, 100);
    *images_map["field"] = images_map["field"]->scaled(100, 100);
    *images_map["shop"] = images_map["shop"]->scaled(100, 100);
}

void Game::setup_scene(){
    background_color = new QColor(128, 200, 42);
    view->set_bg_color(background_color);
    view->set_size({MAP_WIDTH, MAP_HEIGHT});
    // view->zoom(3);
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

GraphicsView *Game::get_view(){
    return view;
}

QPixmap *Game::get_img(std::string img){
    return images_map[img];
}