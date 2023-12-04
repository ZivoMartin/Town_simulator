#include "Game.h"

Game::Game(GraphicsView *view): QMainWindow(){
    dragging.dragging = false;
    view->set_game(this);
    this->view = view;
    load_images();
    load_colors();
    build_info_bubble();
    setup_scene();
    init_game();
    play();
}

Game::~Game(){
    free_vec<Field*>(field_vec);
    free_vec<Shop*>(shop_vec);
    free_vec<House*>(house_vec);
    free_map(images_map);
    free_map(top_info);
    delete background_color;
}


template <typename K, typename V>
void Game::free_map(std::map<K, V> map){
    for(auto el: map){
        std::cout << el.first << std::endl;
        delete map[el.first];
    }
}

void Game::init_game(){
    create_new_building("field", {34*CASE_SIZE, 28*CASE_SIZE});
    create_new_building("shop", {36*CASE_SIZE, 22*CASE_SIZE});
    create_new_building("house", {23*CASE_SIZE, 36*CASE_SIZE});
}

void Game::play(){
    QTimer::singleShot(FRAME_SPEED, this, [=](){
        iter += 1;
        if(iter%10 == 0){
            update_info();    
        }
        view->update();
    });
}

void Game::load_colors(){
    QColor top_info(255, 255, 153);
    color_map["top_info"] = top_info;
    QColor top_ratio(255, 150, 153);
    color_map["top_ratio"] = top_ratio;
}

void Game::build_info_bubble(){
    top_info["nb_gold"] = new InfoZone(this, {30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Golds: ", color_map["top_info"], BASE_GOLD);
    top_info["nb_food"] = new InfoZone(this, {info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Food: ", color_map["top_info"], BASE_FOOD);
    top_info["nb_citizen"] = new InfoZone(this, {30+2*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Citizens: ", color_map["top_info"], BASE_CITIZEN);
    top_info["nb_worker"] = new InfoZone(this, {30+3*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Workers: ", color_map["top_info"], 0);
    top_info["nb_non_worker"] = new InfoZone(this, {30+4*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Unemployeds: ", color_map["top_info"], BASE_CITIZEN);
    top_info["nb_gold_ratio"] = new InfoZone(this, {30+5*info_bubble_dims.x+30 + 200, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Gold ratio: ", color_map["top_ratio"], 0);
    top_info["nb_food_ratio"] = new InfoZone(this, {30+6*info_bubble_dims.x+30 + 200, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Food ratio: ", color_map["top_ratio"], -BASE_CITIZEN);
    top_info["nb_citizen_ratio"] = new InfoZone(this, {30+7*info_bubble_dims.x+30 + 200, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Citizen ratio: ", color_map["top_ratio"], 0);
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

void Game::update_info(){
    top_info["nb_gold"]->set_value(top_info["nb_gold"]->get_value()+top_info["nb_gold_ratio"]->get_value());
    top_info["nb_food"]->set_value(top_info["nb_food"]->get_value()+top_info["nb_food_ratio"]->get_value());
}

void Game::click_release(Xy stop_pos){
    if(is_dragging()){
        Xy size = apply_get_method(&dragging.item, &Building::get_size);
        Xy *origin_pos = apply_get_method(&dragging.item, &Building::get_origin_pos);
        Xy tab_new_pos = coord_to_tab(&stop_pos);
        correct_pos(&tab_new_pos, &size);
        stop_pos = tab_to_coord(&tab_new_pos);
        if(is_empty_place(&stop_pos, &size)){
            erase_zone(origin_pos, &size);
            apply_method(&dragging.item, &Building::set_origin_pos, stop_pos);
            if(dragging.item.type == FIELD){
                new_building(dragging.item.building.field, &Game::set_case_field);
            }else if(dragging.item.type == HOUSE){
                new_building(dragging.item.building.house, &Game::set_case_house);
            }else{
                new_building(dragging.item.building.shop, &Game::set_case_shop);
            }
        }else{
            apply_method(&dragging.item, &Building::drag, *origin_pos);
        }
        dragging.dragging = false;
    }    
}

void Game::mouse_move(Xy pos){
    if(is_dragging()){
        apply_method(&dragging.item, &Building::drag, pos);
    }
}

template <typename T, typename G>
G Game::apply_method(build_tab_case *building, G (Building::*f)(T), T arg){
    switch (building->type){
        case FIELD:
            return (building->building.field->*f)(arg);
        case SHOP:
            return (building->building.shop->*f)(arg);
        case HOUSE:
            return (building->building.house->*f)(arg);     
        case EMPTY:
            exit(EXIT_FAILURE); 
    }
}

template <typename G>
G Game::apply_get_method(build_tab_case *building, G (Building::*f)()){
    switch (building->type){
        case FIELD:
            return (building->building.field->*f)();
        case SHOP:
            return (building->building.shop->*f)();
        case HOUSE:
            return (building->building.house->*f)();     
        case EMPTY:
            exit(EXIT_FAILURE);   
    }
    exit(EXIT_FAILURE);
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
            Shop *new_building = new Shop(this, pos);
            shop_vec.push_back(new_building);
            this->new_building(new_building, &Game::set_case_shop);
        } else if (type == "house") {
            House *new_building = new House(this, pos);
            house_vec.push_back(new_building);
            this->new_building(new_building, &Game::set_case_house);
        } else if (type == "field") {
            Field *new_building = new Field(this, pos);
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

void Game::erase_zone(Xy *pos_without_convert, Xy *s) {
    Xy pos = coord_to_tab(pos_without_convert);
    int s_x = (s->x/2)/CASE_SIZE;
    int s_y = (s->y/2)/CASE_SIZE;
    for (int i = 0; i < s_x; i++) {
        for (int j = 0; j < s_y; j++) {
            set_case_empty({pos.x+i, pos.y+j});
            set_case_empty({pos.x+i, pos.y-j});
            set_case_empty({pos.x-i, pos.y+j});
            set_case_empty({pos.x-i, pos.y-j});
        }
    }
}

bool Game::is_empty_place(Xy *pos_without_convert, Xy *size){
    Xy pos = coord_to_tab(pos_without_convert);
    int s_x = (size->x/2)/CASE_SIZE + 1;
    int s_y = (size->y/2)/CASE_SIZE + 1;
    for (int i = 0; i < s_x; i++) {
        for (int j = 0; j < s_y; j++) {
            if(get_map_tab_case({pos.x+i, pos.y+j}) != nullptr && !its_dragged_item_case({pos.x+i, pos.y+j})){
                return false;
            } 
            if(get_map_tab_case({pos.x+i, pos.y-j}) != nullptr && !its_dragged_item_case({pos.x+i, pos.y-j})){
                return false;
            } 
            if(get_map_tab_case({pos.x-i, pos.y+j}) != nullptr && !its_dragged_item_case({pos.x-i, pos.y+j})){
                return false;
            } 
            if(get_map_tab_case({pos.x-i, pos.y-j}) != nullptr && !its_dragged_item_case({pos.x-i, pos.y-j})){
                return false;
            }
        }
    }
    return true;
}

bool Game::its_dragged_item_case(Xy pos){
    if(is_dragging()){
        build_tab_case *c = get_map_tab_case({pos.x, pos.y});
        if(c->type == FIELD){
            return dragging.item.type == FIELD && c->building.field == dragging.item.building.field;
        }else if(c->type == SHOP){
            return dragging.item.type == SHOP && c->building.shop == dragging.item.building.shop;
        }else{
            return dragging.item.type == HOUSE && c->building.house == dragging.item.building.house;
        }
    }
    return false;
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
void Game::correct_pos(Xy *tab_pos, Xy *size){
    if(tab_pos->x-(size->x/2)/CASE_SIZE<0){
        tab_pos->x = (size->x/2)/CASE_SIZE;
    }
    if(tab_pos->y-(size->y/2)/CASE_SIZE<0){
        tab_pos->y = (size->y/2)/CASE_SIZE;
    }
    if(tab_pos->x+(size->x/2)/CASE_SIZE>=map_case_dim.x){
        tab_pos->x = map_case_dim.x-(size->x/2)/CASE_SIZE-1;
    }
    if(tab_pos->y+(size->x/2)/CASE_SIZE>=map_case_dim.y){
        tab_pos->y = map_case_dim.y-(size->y/2)/CASE_SIZE-1;
    }
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