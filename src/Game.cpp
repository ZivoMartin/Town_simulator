#include "Game.h"

Game::Game(GraphicsView *view): QMainWindow(){
    view->set_game(this);
    this->view = view;
    load_images();
    setup_scene();
    map_case_dim = {MAP_WIDTH/CASE_SIZE, MAP_HEIGHT/CASE_SIZE};
    init_game();
    play();
}

Game::~Game(){
    free_vec<Field*>(field_vec);
    free_vec<Shop*>(shop_vec);
    free_vec<House*>(house_vec);
    delete images_map["house"];
    delete images_map["field"];
    delete images_map["shop"];
    delete background_color;
    delete view;
}

void Game::init_game(){
    create_new_building("field", {21, 32});
    create_new_building("shop", {26, 23});
    create_new_building("house", {51, 30});
}

void Game::play(){
    QTimer::singleShot(FRAME_SPEED, this, [=](){
        iter += 1;
    });
}


void Game::screen_clicked(Xy coord_click){
    build_tab_case *clicked_case = get_map_tab_case(coord_to_tab(&coord_click));
    if(clicked_case == nullptr){
        
    }else{
        dragging = {true, *clicked_case};
        if(clicked_case->type == FIELD){
            
        }else if(clicked_case->type == HOUSE){
            
        }else{
            
        }
    }
}

void Game::click_release(){
    dragging.dragging = false;
}

void Game::mouse_move(Xy pos){
    if(is_dragging()){
        dragging->item()
    }
}

template <typename T>
void Game::free_vec(std::vector<T> vec){
    for(unsigned int i=0; i<vec.size(); i++){
        delete vec[i];
    }
}

int Game::get_iter(){
    return iter;
}
bool Game::is_dragging(){
    return dragging.dragging;
}
void Game::load_images(){
    std::string t[] = {"field", "house", "shop"};

    dim_img_map["field"] = {80, 80};
    dim_img_map["house"] = {80, 80};
    dim_img_map["shop"] = {80, 80};

    for(int i=0; i<3; i++){ 
        images_map[t[i]] = new QPixmap();
        images_map[t[i]]->load(QString::fromStdString("../images/"+ t[i] + ".png"));
        *images_map[t[i]] = images_map[t[i]]->scaled(dim_img_map[t[i]].x, dim_img_map[t[i]].y);
    }
}

void Game::setup_scene(){
    background_color = new QColor(128, 200, 42);
    view->set_bg_color(background_color);
    view->set_size({MAP_WIDTH, MAP_HEIGHT});
    // view->zoom(3);
}

GraphicsView *Game::get_view(){
    return view;
}

QPixmap *Game::get_img(std::string img){
    return images_map[img];
}

Xy *Game::get_img_size(std::string img){
    return &dim_img_map[img];
}

void Game::create_new_building(std::string type, Xy pos){
    if (is_empty_place(&pos, get_img_size(type))){
        if (type == "shop") {
            Shop *new_building = new Shop(this, tab_to_coord(&pos));
            shop_vec.push_back(new_building);
            this->new_building(new_building, &Game::set_case_shop);
        } else if (type == "house") {
            House *new_building = new House(this, tab_to_coord(&pos));
            house_vec.push_back(new_building);
            this->new_building(new_building, &Game::set_case_house);
        } else if (type == "field") {
            Field *new_building = new Field(this, tab_to_coord(&pos));
            field_vec.push_back(new_building);
            this->new_building(new_building, &Game::set_case_field);
        }
    }
}

template <typename T>
void Game::new_building(T *new_building, void (Game::*f)(Xy, T*)) {
    Xy pos = coord_to_tab(new_building->get_pos());
    Xy s = new_building->get_size();
    int s_x = (s.x/2)/CASE_SIZE;
    int s_y = (s.y/2)/CASE_SIZE;
    for (int i = 0; i < s_x; i++) {
        for (int j = 0; j < s_y; j++) {
            (this->*f)({pos.x+i, pos.y+j}, new_building);
            (this->*f)({pos.x+i, pos.y-j}, new_building);
            (this->*f)({pos.x-i, pos.y+j}, new_building);
            (this->*f)({pos.x-i, pos.y-j}, new_building);
        }
    }
}

bool Game::is_empty_place(Xy *pos, Xy *size){
    int s_x = (size->x/2)/CASE_SIZE + 1;
    int s_y = (size->y/2)/CASE_SIZE + 1;
    for (int i = 0; i < s_x; i++) {
        for (int j = 0; j < s_y; j++) {
            if(get_map_tab_case({pos->x+i, pos->y+j}) != nullptr || get_map_tab_case({pos->x+i, pos->y-j}) != nullptr || get_map_tab_case({pos->x-i, pos->y+j}) != nullptr || get_map_tab_case({pos->x-i, pos->y-j}) != nullptr){
                return false;
            }
        }
    }
    return true;
}

void Game::set_case_field(Xy pos, Field *field){
    int converted_pos = convert_one_dim(&pos);
    map_tab[converted_pos].type = FIELD;
    map_tab[converted_pos].building.field = field;
}

void Game::set_case_shop(Xy pos, Shop *shop){
    int converted_pos = convert_one_dim(&pos);
    map_tab[converted_pos].type = SHOP;
    map_tab[converted_pos].building.shop = shop;
}

void Game::set_case_house(Xy pos, House *house){
    int converted_pos = convert_one_dim(&pos);
    map_tab[converted_pos].type = HOUSE;
    map_tab[converted_pos].building.house = house;
}

void Game::set_case_empty(Xy pos){
    map_tab.erase(convert_one_dim(&pos));
}

build_tab_case *Game::get_map_tab_case(Xy pos){
    int converted_pos = convert_one_dim(&pos);
    if(map_tab.count(converted_pos)){
        return &map_tab[converted_pos];
    }
    return nullptr;
}    


Xy Game::coord_to_tab(Xy *entry){
    return {entry->x/CASE_SIZE, entry->y/CASE_SIZE};
}

Xy Game::tab_to_coord(Xy *entry){
    return {entry->x*CASE_SIZE, entry->y*CASE_SIZE};
}

int Game::convert_one_dim(Xy *pos){
    return pos->x*map_case_dim.x+pos->y;
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