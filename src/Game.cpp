#include "Game.h"

Game::Game(GraphicsView *view): QMainWindow(){
    dragging.dragging = false;
    view->set_game(this);
    this->view = view;
    load_images();
    load_colors();
    setup_scene();
    build_info_bubble();
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
    delete view;
}


void Game::init_game(){
    create_new_building("field", {34*CASE_SIZE, 30*CASE_SIZE});
    create_new_building("shop", {38*CASE_SIZE, 22*CASE_SIZE});
    create_new_building("house", {28*CASE_SIZE, 19*CASE_SIZE});
    create_new_building("house", {35*CASE_SIZE, 15*CASE_SIZE});
    
    current_stat["gold"] = BASE_GOLD;
    current_stat["food"] = BASE_FOOD;
    current_stat["citizen"] = BASE_CITIZEN;
    
    Xy pos = {screen_size.x-shop_setting_size.x, screen_size.y-shop_setting_size.y};
    shop_menu_setting = new Setting(this, pos, shop_setting_size);
    shop_menu_setting->add_img(new GraphicsPixmapItem(get_img("field"), view->get_scene(), {pos.x+200, pos.y+120}));
    shop_menu_setting->add_img(new GraphicsPixmapItem(get_img("house"), view->get_scene(), {pos.x+400, pos.y+120}));
    shop_menu_setting->add_img(new GraphicsPixmapItem(get_img("shop"), view->get_scene(), {pos.x+600, pos.y+120}));
    Xy *s_shop_button = get_img_size("shop_icon");
    PushButton *shop_button = new PushButton(this, {screen_size.x-s_shop_button->x, screen_size.y-s_shop_button->y}, *s_shop_button, &Game::open_shop, "open_shop", get_img("shop_icon"));
    add_button(shop_button);
    shop_button->add();
}

void Game::play(){
    QTimer::singleShot(FRAME_SPEED, this, [=](){
        iter += 1;
        if(iter%10 == 0){
            update_info();    
        }
        view->update();
        play();
    });
}

void Game::load_colors(){
    color_map["top_info"] = QColor(255, 255, 153);
    color_map["top_ratio"] = QColor(255, 150, 153);
    color_map["settings"] = QColor(220, 220, 220);
    color_map["close_button"] = QColor(255, 0, 0);
    color_map["building_add_worker_button"] = QColor(50, 200, 0);
    color_map["building_less_worker_button"] = QColor(255, 200, 100);
    color_map["increase_worker"] = QColor(255, 255, 153);
    color_map["decrease_worker"] = QColor(255, 133, 132);
    color_map["lvl_info"] = QColor(200, 200, 200);
}

void Game::build_info_bubble(){
    top_info["nb_gold"] = new InfoZone(this, {30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Golds: ", color_map["top_info"], CIRCLE, "nb_gold");
    top_info["nb_food"] = new InfoZone(this, {info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Food: ", color_map["top_info"], CIRCLE, "nb_food");
    top_info["nb_citizen"] = new InfoZone(this, {30+2*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Citizens: ", color_map["top_info"], CIRCLE, "nb_food");
    top_info["nb_worker"] = new InfoZone(this, {30+3*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Workers: ", color_map["top_info"], CIRCLE, "nb_worker");
    top_info["nb_non_worker"] = new InfoZone(this, {30+4*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Unemployeds: ", color_map["top_info"], CIRCLE, "nb_non_worker");
    top_info["gold_ratio"] = new InfoZone(this, {30+5*info_bubble_dims.x+30 + 200, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Gold ratio: ", color_map["top_ratio"], CIRCLE, "gold_ratio");
    top_info["food_ratio"] = new InfoZone(this, {30+6*info_bubble_dims.x+30 + 200, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Food ratio: ", color_map["top_ratio"], CIRCLE, "food_ratio");
    top_info["citizen_ratio"] = new InfoZone(this, {30+7*info_bubble_dims.x+30 + 200, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Citizen ratio: ", color_map["top_ratio"], CIRCLE, "nb_citizen_ratio");
    
    top_info["nb_gold"]->set_value(BASE_GOLD);
    top_info["nb_food"]->set_value(BASE_FOOD);
    top_info["nb_citizen"]->set_value(BASE_CITIZEN);
    top_info["nb_worker"]->set_value(0.0);
    top_info["nb_non_worker"]->set_value(BASE_CITIZEN);
    top_info["gold_ratio"]->set_value(-1);
    top_info["food_ratio"]->set_value(-BASE_CITIZEN/10);
    top_info["citizen_ratio"]->set_value(BASE_CITIZEN/factor_citizen_ratio);    

    for(auto elt: top_info){
        top_info[elt.first]->add();
    }
}

void Game::open_shop(){
    if(current_open_setting.setting != nullptr){
        close_current_setting();
    }
    set_current_setting(shop_menu_setting, nullptr);
}

void Game::screen_clicked(Xy coord_click){
    if(its_a_button_click(&coord_click)){

    }else if(current_open_setting.setting == nullptr){
        build_tab_case *clicked_case = get_map_tab_case(coord_to_tab(&coord_click));
        if(clicked_case == nullptr){

        }else{
            dragging = {true, *clicked_case};
        }       
    }
}

void Game::set_current_setting(Setting *setting, build_tab_case *building){
    current_open_setting.setting = setting;
    current_open_setting.building = building;
    setting->open();
}

QColor Game::get_color(std::string color){
    return color_map[color];
}

void Game::update_info(){
    current_stat["gold"] += top_info["gold_ratio"]->get_value();
    top_info["nb_gold"]->set_value(static_cast<int>(current_stat["gold"]));
    float new_food = current_stat["food"]+top_info["food_ratio"]->get_value();
    if(new_food > 0){
        current_stat["food"] = new_food;
        top_info["nb_food"]->set_value(static_cast<int>(new_food));    
    }else{
        current_stat["citizen"] -= 1;
        top_info["nb_citizen"]->set_value(static_cast<int>(current_stat["citizen"]));
    }
    current_stat["citizen"] += top_info["citizen_ratio"]->get_value();
    int new_citizen_nb = current_stat["citizen"];
    int display_citizen_nb = top_info["nb_citizen"]->get_value();
    if(new_citizen_nb > display_citizen_nb){
        if(new_citizen_nb <= max_citizen){
            top_info["citizen_ratio"]->set_value(new_citizen_nb/factor_citizen_ratio);
            top_info["nb_citizen"]->set_value(new_citizen_nb);
            top_info["nb_non_worker"]->set_value(top_info["nb_non_worker"]->get_value() + (new_citizen_nb-display_citizen_nb));
            nb_citizen = new_citizen_nb;
            nb_unemployed += (new_citizen_nb-display_citizen_nb);
            update_food_ratio();
        }
    }
}

void Game::click_release(Xy stop_pos){
    if(is_dragging()){
        Xy *origin_pos = apply_method_0(&dragging.item, &Building::get_origin_pos);
        Xy *current_pos = apply_method_0(&dragging.item, &Building::get_current_pos);
        if(origin_pos->x != current_pos->x || origin_pos->y != current_pos->y){
            Xy size = apply_method_0(&dragging.item, &Building::get_size);
            Xy tab_new_pos = coord_to_tab(&stop_pos);
            correct_pos(&tab_new_pos, &size);
            stop_pos = tab_to_coord(&tab_new_pos);
            if(is_empty_place(&stop_pos, &size)){
                erase_zone(origin_pos, &size);
                apply_method_1(&dragging.item, &Building::set_origin_pos, stop_pos);
                if(dragging.item.type == FIELD){
                    new_building(dragging.item.building.field, &Game::set_case_field);
                }else if(dragging.item.type == HOUSE){
                    new_building(dragging.item.building.house, &Game::set_case_house);
                }else{
                    new_building(dragging.item.building.shop, &Game::set_case_shop);
                }
            }else{
                apply_method_1(&dragging.item, &Building::drag, *origin_pos);
            }
        }else{
            if(dragging.item.type == FIELD){
                dragging.item.building.field->clicked();
            }else if(dragging.item.type == HOUSE){
                dragging.item.building.house->clicked();
            }else{
                dragging.item.building.shop->clicked();
            }
        }
        dragging.dragging = false;
    }    
}

void Game::mouse_move(Xy pos){
    if(is_dragging()){
        apply_method_1(&dragging.item, &Building::drag, pos);
    }
}

template <typename T, typename G>
G Game::apply_method_1(build_tab_case *building, G (Building::*f)(T), T arg){
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
G Game::apply_method_0(build_tab_case *building, G (Building::*f)()){
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


int Game::get_iter(){
    return iter;
}
bool Game::is_dragging(){
    return dragging.dragging;
}
void Game::load_images(){
    std::string t[] = {"field", "house", "shop", "close_button", "less", "more", "shop_icon"};

    dim_img_map["field"] = {FIELD_WIDTH, FIELD_HEIGHT};
    dim_img_map["house"] = {HOUSE_WIDTH, HOUSE_HEIGHT};
    dim_img_map["shop"] = {SHOP_WIDTH, SHOP_HEIGHT};
    dim_img_map["close_button"] = {30, 30};
    dim_img_map["more"] = {30, 30};
    dim_img_map["less"] = {30, 30};
    dim_img_map["shop_icon"] = {120, 120};

    for(int i=0; i<7; i++){ 
        images_map[t[i]] = new QPixmap();
        images_map[t[i]]->load(QString::fromStdString("../images/"+ t[i] + ".png"));
        *images_map[t[i]] = images_map[t[i]]->scaled(dim_img_map[t[i]].x, dim_img_map[t[i]].y);
    }
    images_map["bg"] = new QPixmap();
    images_map["bg"]->load(QString::fromStdString("../images/bg.png"));
}

void Game::setup_scene(){
    background_color = new QColor(128, 200, 42);
    view->set_bg_color(background_color);
    QScreen *screen = QGuiApplication::primaryScreen();
    this->screen_size = {screen->geometry().width() - 30, screen->geometry().height() - 30};
    map_case_dim = {screen_size.x/CASE_SIZE, screen_size.y/CASE_SIZE};
    view->set_size(screen_size);
    // bg_img = new QGraphicsPixmapItem(*images_map["bg"]);
    // bg_img->setTransformOriginPoint(images_map["bg"]->rect().center());
    // bg_img->setScale(qreal(view->get_scene()->width()) / qreal(images_map["bg"]->width()), 
    //                          qreal(view->get_scene()->height()) / qreal(images_map["bg"]->height()));
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

Xy *Game::get_size_setting_building(){
    return &size_settings_building;
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


void Game::close_current_setting(){
    current_open_setting.setting->close();
    current_open_setting = {nullptr, nullptr};
}

void Game::add_button(PushButton *new_button){
    button_vec.push_back(new_button);
}

void Game::erase_button(PushButton *button){
    for(unsigned int i=0; i<button_vec.size(); i++){
        if(button_vec[i] == button){
            button_vec.erase(button_vec.begin()+i);
            break;
        }
    }
}

bool Game::its_a_button_click(Xy *pos){
    for(unsigned int i=0; i<button_vec.size(); i++){
        if(button_vec[i]->is_it(pos)){
            button_vec[i]->is_clicked();
            return true;
        }
    }
    return false;
}

void Game::add_worker(){
    if(nb_worker<nb_citizen){
        if(apply_method_0(current_open_setting.building, &Building::add_worker)){
            nb_worker += 1;
            nb_unemployed -= 1;
            top_info["nb_worker"]->set_value(nb_worker);
            top_info["nb_non_worker"]->set_value(nb_unemployed);
        }
    }
}

void Game::remove_worker(){
    if(nb_unemployed<nb_citizen){
        if(apply_method_0(current_open_setting.building, &Building::pull_worker)){
            nb_worker -= 1;
            nb_unemployed += 1;
            top_info["nb_worker"]->set_value(nb_worker);
            top_info["nb_non_worker"]->set_value(nb_unemployed);
        }
    }
}

void Game::update_food_ratio(){
    float new_food_ratio = -(nb_citizen/10);
    for(unsigned int i = 0; i<field_vec.size(); i++){
        new_food_ratio += field_vec[i]->get_efficiency();
    }
    top_info["food_ratio"]->set_value(new_food_ratio);
}

void Game::update_gold_ratio(){
    int nb_building = field_vec.size()+shop_vec.size()+house_vec.size();
    float new_gold_ratio = -(nb_building/3);
    for(unsigned int i = 0; i<shop_vec.size(); i++){
        new_gold_ratio += shop_vec[i]->get_efficiency();
    }
    top_info["gold_ratio"]->set_value(new_gold_ratio);
}

template <typename K, typename V>
void free_map(std::map<K, V> map){
    for(auto el: map){
        delete map[el.first];
    }
}

template <typename T>
void free_vec(std::vector<T> vec){
    for(unsigned int i=0; i<vec.size(); i++){
        delete vec[i];  
    }
}