#include "Game.h"

Game::Game(QApplication *app, GraphicsView *view): QMainWindow(){
    view->showFullScreen();
    view->show();
    view->set_game(this);
    this->view = view;
    this->app = app;
    dragging.dragging = false;
    load_images();
    load_colors();
    setup_scene();
    build_param();
    build_info_bubble();
    build_shop();
    menu = new Menu(this);
}


void Game::start(){
    iter = 0;
    init_info_bubble();
    shop_button->add();
    init_game();
    play();
}

void Game::start_signal(){
    menu->start_game();
}

void Game::quit_app(){
    app->quit();
}

Game::~Game(){
    clean_building();
    free_map(&images_map);
    free_map(&top_info);

    if(try_to_buy != EMPTY){
        delete try_to_buy_img;
    }

    delete bg_img;
    delete shop_menu_setting;
    delete background_color;
    delete menu;
    delete freez_img;
    delete citizen_bar;
    delete param;
    delete view;
}

void Game::clean_building(){
    free_vec<Field*>(&field_vec);
    free_vec<Shop*>(&shop_vec);
    free_vec<House*>(&house_vec);
    free_vec<Farm*>(&farm_vec);
}

void Game::reset(){
    clean_building();
    for(auto el: top_info){
        top_info[el.first]->remove();
    }
    citizen_bar->stop_load();
    citizen_bar->reset_load();
    citizen_bar->remove();
    shop_button->remove();
    frame_speed = 20;
}

void Game::init_game(){
    nb_citizen = BASE_CITIZEN;
    nb_worker = 0;
    nb_unemployed = BASE_CITIZEN;
    max_citizen = 0;
    gold_limit = -100;

    current_stat["gold"] = BASE_GOLD;
    current_stat["food"] = BASE_FOOD;
    current_stat["citizen"] = BASE_CITIZEN;

    building_price["shop"] = 50;
    building_price["house"] = 25;
    building_price["field"] = 50;
    building_price["farm"] = 50;

    create_new_building("field", {34*CASE_SIZE, 30*CASE_SIZE});
    create_new_building("shop", {38*CASE_SIZE, 22*CASE_SIZE});
    create_new_building("house", {28*CASE_SIZE, 19*CASE_SIZE});
    create_new_building("house", {35*CASE_SIZE, 15*CASE_SIZE});
    create_new_building("farm", {50*CASE_SIZE, 15*CASE_SIZE});

    citizen_bar->load();
}

void Game::build_shop(){
    Xy pos = {screen_size.x-shop_setting_size.x, screen_size.y-shop_setting_size.y};
    std::string t[] = {"farm", "field", "house", "shop"};

    shop_img_pos["farm"] = {pos.x+100, pos.y+75};
    for(int i=1; i<4; i++){
        shop_img_pos[t[i]] = {pos.x+(i)*200+100, pos.y+75};
    }

    shop_menu_setting = new Setting(this, pos, shop_setting_size, nullptr);
    shop_menu_setting->add_button(new PushButton(this, shop_img_pos["field"], *get_img_size("field"), &Game::try_to_buy_field, "field", get_img("field")));
    shop_menu_setting->add_button(new PushButton(this, shop_img_pos["house"], *get_img_size("house"), &Game::try_to_buy_house, "house", get_img("house")));
    shop_menu_setting->add_button(new PushButton(this, shop_img_pos["shop"], *get_img_size("shop"), &Game::try_to_buy_shop, "shop", get_img("shop")));
    shop_menu_setting->add_button(new PushButton(this, shop_img_pos["farm"], *get_img_size("farm_icon"), &Game::try_to_buy_farm, "farm", get_img("farm_icon")));

    shop_menu_setting->add_info_zone(new InfoZone(this, {pos.x+330, pos.y+75+FIELD_HEIGHT+5}, {50, 30}, "$", get_color("price"), RECT, "field"));
    shop_menu_setting->add_info_zone(new InfoZone(this, {pos.x+530, pos.y+75+HOUSE_HEIGHT+5}, {50, 30}, "$", get_color("price"), RECT, "house"));
    shop_menu_setting->add_info_zone(new InfoZone(this, {pos.x+730, pos.y+75+SHOP_HEIGHT+5}, {50, 30}, "$", get_color("price"), RECT, "shop"));
    shop_menu_setting->add_info_zone(new InfoZone(this, {pos.x+130, pos.y+75+BUILDING_ICON_HEIGHT+5}, {50, 30}, "$", get_color("price"), RECT, "farm"));

    Xy *s_shop_button = get_img_size("shop_icon");
    this->shop_button = new PushButton(this, {screen_size.x-s_shop_button->x, screen_size.y-s_shop_button->y}, *s_shop_button, &Game::open_shop, "open_shop", get_img("shop_icon"));
}

void Game::play(){
    QTimer::singleShot(frame_speed, this, [=](){
        iter += 1;
        if(iter%10 == 0 && !pause){
            update_info();    
        }
        view->update();
        if(!menu->get_activity()){
            play();
        }
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
    color_map["price"] = QColor(255, 255, 153);
    color_map["upgrade_price"] = QColor(0, 255, 0);
    color_map["sold_price"] = QColor(255, 0, 0);
    color_map["reverse_info_color"] = QColor(200, 200, 200);
}

void Game::build_info_bubble(){
    top_info["nb_gold"] = new InfoZone(this, {30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Golds: ", color_map["top_info"], CIRCLE, "nb_gold");
    top_info["nb_food"] = new InfoZone(this, {info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Food: ", color_map["top_info"], CIRCLE, "nb_food");
    top_info["nb_citizen"] = new InfoZone(this, {30+2*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Citizens: ", color_map["top_info"], CIRCLE, "nb_food");
    top_info["nb_worker"] = new InfoZone(this, {30+3*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Workers: ", color_map["top_info"], CIRCLE, "nb_worker");
    top_info["nb_non_worker"] = new InfoZone(this, {30+4*info_bubble_dims.x+30, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Unemployeds: ", color_map["top_info"], CIRCLE, "nb_non_worker");
    top_info["gold_ratio"] = new InfoZone(this, {30+5*info_bubble_dims.x+30 + 100, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Gold ratio: ", color_map["top_ratio"], CIRCLE, "gold_ratio");
    top_info["food_ratio"] = new InfoZone(this, {30+6*info_bubble_dims.x+30 + 100, 0}, {info_bubble_dims.x, info_bubble_dims.y}, "Food ratio: ", color_map["top_ratio"], CIRCLE, "food_ratio");
    top_info["nb_citizen"]->add_son(new InfoZone(this, {58, 38}, {0, 0}, "Max: ", QColor(255, 255, 255), WITHOUT, "max_citizen"));
    top_info["nb_citizen"]->set_value_of_a_son(max_citizen, "max_citizen");
    top_info["nb_food"]->add_son(new InfoZone(this, {58, 38}, {0, 0}, "Max: ", QColor(255, 255, 255), WITHOUT, "max_food"));
    top_info["nb_food"]->set_value_of_a_son(0, "max_food");
    citizen_bar = new LoadingBar(this, {30+7*info_bubble_dims.x+30 + 130, 20}, {200, 40}, &Game::citizen_bar_complete, "New citizen");
    citizen_bar->set_ratio(BASE_CITIZEN/10);
}

void Game::init_info_bubble(){
    top_info["nb_gold"]->set_value(BASE_GOLD);
    top_info["nb_food"]->set_value(BASE_FOOD);
    top_info["nb_citizen"]->set_value(BASE_CITIZEN);
    top_info["nb_worker"]->set_value(0.0);
    top_info["nb_non_worker"]->set_value(BASE_CITIZEN);
    top_info["gold_ratio"]->set_value(-1);
    top_info["food_ratio"]->set_value(-BASE_CITIZEN/10);
    citizen_bar->add();
    for(auto elt: top_info){
        top_info[elt.first]->add();
    }
}


void Game::open_shop(){
    if(current_open_setting.setting != nullptr){
        close_current_setting();
    }
    shop_button->remove();
    set_current_setting(shop_menu_setting, nullptr);
}

void Game::screen_clicked(Xy coord_click){
    if(!its_a_button_click(&coord_click)){
        build_tab_case *clicked_case = get_map_tab_case(coord_to_tab(&coord_click));
        if(clicked_case == nullptr){
            if(current_open_setting.setting != nullptr && !current_open_setting.setting->is_it(&coord_click)){
                close_current_setting();
            }
        }else if(current_open_setting.setting == nullptr){
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
    increase_gold(top_info["gold_ratio"]->get_value());
    float new_food = current_stat["food"]+top_info["food_ratio"]->get_value();
    if(new_food > 0 && new_food < max_food){
        current_stat["food"] = new_food;
        top_info["nb_food"]->set_value(static_cast<int>(new_food));    
    }else if(new_food <= 0){
        kill_a_citizen();       
    }
}

void Game::kill_a_citizen(){
    current_stat["citizen"] -= 1;
    top_info["nb_citizen"]->set_value(static_cast<int>(current_stat["citizen"]));
    nb_citizen -= 1;
    if(nb_citizen <= max_citizen){
        top_info["nb_citizen"]->set_text_color(QColor(0, 0, 0));
    }
    if(nb_citizen <= 0){
        end_game("Lost by famine, wanna restart ?");
    }else if(nb_unemployed >0){
        nb_unemployed -= 1;
        top_info["nb_non_worker"]->set_value(nb_unemployed);
    }else{
        for(unsigned int i=0; i<field_vec.size(); i++){
            if(field_vec[i]->get_nb_worker() != 0){
                field_vec[i]->pull_worker();
                return;
            }
        }
        for(unsigned int i=0; i<shop_vec.size(); i++){
            if(shop_vec[i]->get_nb_worker() != 0){
                shop_vec[i]->pull_worker();
                break;
            }
        }
    }
}

void Game::citizen_bar_complete(){
    add_citizen();
    citizen_bar->set_ratio(nb_citizen/10);
    citizen_bar->load();
}

void Game::click_release(Xy stop_pos){
    if(!menu->get_activity() && is_dragging()){
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
    }else if(!menu->get_activity() && try_to_buy != EMPTY){
        delete try_to_buy_img;
        std::string str = "shop"; 
        if(try_to_buy == FIELD) str = "field";
        if(try_to_buy == HOUSE) str = "house";
        if(try_to_buy == FARM) str = "farm";
        if(create_new_building(str, stop_pos)){
            increase_gold(-(building_price[str] - price_to_add));
        }

        try_to_buy = EMPTY;
    }
}

void Game::mouse_move(Xy pos){
    if(is_dragging()){
        apply_method_1(&dragging.item, &Building::drag, pos);
    }else if(try_to_buy != EMPTY){
        try_to_buy_img->set_pos_img(pos);
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
        case FARM:
            return (building->building.farm->*f)(arg);
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
        case FARM:
            return (building->building.farm->*f)();  
        case EMPTY:
            exit(EXIT_FAILURE);   
    }
    exit(EXIT_FAILURE);
}

int Game::get_max_food(){
    return max_food;
}

void Game::set_max_food(int x){
    max_food = x;
    top_info["nb_food"]->set_value_of_a_son(x, "max_food");
}

int Game::get_iter(){
    return iter;
}
bool Game::is_dragging(){
    return dragging.dragging;
}
void Game::load_images(){
    std::vector<std::string> t = {"field", "house", "shop", "close_button", "less", "more", "shop_icon", "been", "lvl_up", "start", "info", "rules_button", "freez", "farm", "farm_icon", "settings", "quit", "restart", "empty"};
    dim_img_map["field"] = {FIELD_WIDTH, FIELD_HEIGHT};
    dim_img_map["house"] = {HOUSE_WIDTH, HOUSE_HEIGHT};
    dim_img_map["shop"] = {SHOP_WIDTH, SHOP_HEIGHT};
    dim_img_map["close_button"] = {30, 30};
    dim_img_map["more"] = {30, 30};
    dim_img_map["less"] = {30, 30};
    dim_img_map["shop_icon"] = {120, 120};
    dim_img_map["been"] = {40, 30};
    dim_img_map["lvl_up"] = {40, 30};
    dim_img_map["start"] = {300, 150};
    dim_img_map["info"] = {30, 30};
    dim_img_map["rules_button"] = {200, 60};
    dim_img_map["freez"] = {50, 50};
    dim_img_map["farm"] = {FARM_WIDTH, FARM_HEIGHT};
    dim_img_map["farm_icon"] = {BUILDING_ICON_WIDTH, BUILDING_ICON_HEIGHT};
    dim_img_map["settings"] = {100, 100};
    dim_img_map["quit"] = {200, 60};
    dim_img_map["restart"] = {200, 60};
    dim_img_map["empty"] = {400, 100};
    for(unsigned int i=0; i<t.size(); i++){ 
        images_map[t[i]] = new QPixmap();
        images_map[t[i]]->load(QString::fromStdString("../images/"+ t[i] + ".png"));
        *images_map[t[i]] = images_map[t[i]]->scaled(dim_img_map[t[i]].x, dim_img_map[t[i]].y);
    }
    images_map["bg"] = new QPixmap();
    images_map["bg"]->load("../images/bg.png");
}

void Game::setup_scene(){
    background_color = new QColor(128, 200, 42);
    view->set_bg_color(background_color);
    QScreen *screen = QGuiApplication::primaryScreen();
    this->screen_size = {screen->geometry().width() - 30, screen->geometry().height() - 30};
    map_case_dim = {screen_size.x/CASE_SIZE, screen_size.y/CASE_SIZE};
    view->set_size(screen_size);
    rules = new Setting(this, {-15, -15}, {screen_size.x+30, screen_size.y+30}, nullptr);
    rules->add_info_zone(new InfoZone(this, {static_cast<int>(screen_size.x*0.2), static_cast<int>(screen_size.y*0.3)}, {0, 0}, rules_txt, QColor(255, 255, 255), WITHOUT, "rules"));
    open_rules_button = new PushButton(this, {screen_size.x - 200, 80}, *get_img_size("rules_button"), &Game::open_rules, "open_rules", get_img("rules_button"));
    freez_img = new GraphicsPixmapItem(get_img("freez"), view->get_scene(), {30, screen_size.y-30});
    *images_map["bg"] = images_map["bg"]->scaled(screen_size.x+100, screen_size.y+200);
    bg_img = new GraphicsPixmapItem(images_map["bg"], view->get_scene(), {static_cast<int>(screen_size.x/2), static_cast<int>(screen_size.y*0.8)});
    bg_img->add_img();
    open_rules_button->add();
}

void Game::build_param(){
    Xy param_pos = {static_cast<int>(screen_size.x*0.35), static_cast<int>(screen_size.y*0.2)};
    param = new Setting(this, param_pos, {600, 500}, nullptr);
    param->set_color(QColor(200, 200, 200));
    param->add_button(new PushButton(this, {param_pos.x+20+100, param_pos.y+100+100}, *get_img_size("empty"), &Game::return_to_menu, "menu", get_img("empty")));
    param->get_button("menu")->set_info_zone("Return to menu");
    param->add_button(new PushButton(this, {param_pos.x+20+100, param_pos.y+100+200+10}, *get_img_size("empty"), &Game::speed_up, "up", get_img("empty")));
    param->get_button("up")->set_info_zone("Up speed");
    param->add_button(new PushButton(this, {param_pos.x+20+100, param_pos.y+100+300+20}, *get_img_size("empty"), &Game::speed_down, "down", get_img("empty")));
    param->get_button("down")->set_info_zone("Down speed");
    param->add_button(new PushButton(this, {param_pos.x+20+100, param_pos.y+100+400+30}, *get_img_size("empty"), &Game::quit_app, "quit", get_img("empty")));
    param->get_button("quit")->set_info_zone("Quit Game");
}

void Game::return_to_menu(){
    close_param();
    end_game("Wanna play a game ?");
}

int Game::get_speed_frame(){
    return frame_speed;
}

void Game::speed_down(){
    frame_speed += 10;
}

void Game::speed_up(){
    if(frame_speed > 10){
        frame_speed -= 10;
    }
}

void Game::open_param(){
    if(param->get_is_open()){
        close_param();
    }else{
        param->open();
        citizen_bar->stop_load();
        pause = true;
    }
    
}

void Game::close_param(){
    param->close();
    if(!freez_img->is_open()){
        citizen_bar->load();
        pause = false;
    }
}

void Game::freez_game(){
    if(!menu->get_activity() && !rules->get_is_open()){
        if(!freez_img->is_open()){
            freez_img->add_img();
            citizen_bar->stop_load();
            pause = true;
        }else{
            freez_img->remove_img();
            citizen_bar->load();
            pause = false;
        }
    }
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

bool Game::create_new_building(std::string type, Xy pos){
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
        }else if(type == "farm"){
            Farm *new_building = new Farm(this, pos);
            farm_vec.push_back(new_building);
            this->new_building(new_building, &Game::set_case_farm);
        }
        update_gold_ratio();
        building_price[type] += price_to_add;
        shop_menu_setting->get_info_zone(type)->set_value(building_price[type]);
        return true;
    }
    return false;
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
        }else if(c->type == FARM){
            return dragging.item.type == FARM && c->building.farm == dragging.item.building.farm;
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

void Game::set_case_farm(Xy pos, Farm *farm){
    int converted_pos = convert_one_dim(&pos);
    map_tab[converted_pos].type = FARM;
    map_tab[converted_pos].building.farm = farm;
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

void Game::add_citizen(){
    nb_citizen += 1;
    if(nb_citizen > max_citizen){
        top_info["nb_citizen"]->set_text_color(Qt::red);
        if(nb_citizen >= surpopulation){
            end_game("You lost because of surpopulation ! Wanna restart ?");
        }
    }
    top_info["nb_citizen"]->set_value(nb_citizen);
    top_info["nb_non_worker"]->set_value(top_info["nb_non_worker"]->get_value() + 1);
    nb_unemployed += 1;
    update_food_ratio();
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
    if(rules->get_is_open()){
        close_rules();
    }else if(param->get_is_open()){
        close_param();
    }else{
        if(shop_menu_setting->get_is_open()) shop_button->add();
        current_open_setting.setting->close();
        current_open_setting = {nullptr, nullptr};
    }
    
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
        if(button_vec[i]->is_it(pos) && (!pause || !button_vec[i]->get_freezable())){
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
    float new_food_ratio = -(float(nb_citizen)/10);
    for(unsigned int i = 0; i<field_vec.size(); i++){
        new_food_ratio += field_vec[i]->get_efficiency();
    }
    top_info["food_ratio"]->set_value(new_food_ratio);
}

void Game::update_gold_ratio(){
    int nb_building = field_vec.size()+shop_vec.size()+house_vec.size();
    float new_gold_ratio = -(float(nb_building)/3);
    for(unsigned int i = 0; i<shop_vec.size(); i++){
        new_gold_ratio += shop_vec[i]->get_efficiency();
    }
    top_info["gold_ratio"]->set_value(new_gold_ratio);
}

void Game::update_max_citizen(){
    int new_max = 0;
    for(unsigned int i=0; i<house_vec.size(); i++){
        new_max += house_vec[i]->get_efficiency();
    }
    max_citizen = new_max;
    top_info["nb_citizen"]->set_value_of_a_son(max_citizen, "max_citizen");
}

void Game::update_max_food(){
    int new_max = 0;
    for(unsigned int i=0; i<farm_vec.size(); i++){
        new_max += farm_vec[i]->get_efficiency();
    }
    max_food = new_max;
    top_info["nb_food"]->set_value_of_a_son(max_food, "max_food");
}


void Game::update_stat(){
    update_gold_ratio();
    update_food_ratio();
    update_max_citizen();
    update_max_food();
}

void Game::try_to_buy_shop(){
    if(current_stat["gold"] >= building_price["shop"]){
        try_to_buy = SHOP;
        try_to_buy_img = new GraphicsPixmapItem(get_img("shop"), view->get_scene(), shop_img_pos["shop"]);
        try_to_buy_img->add_img();
    }
}

void Game::try_to_buy_house(){
    if(current_stat["gold"] >= building_price["house"]){
        try_to_buy = HOUSE;
        try_to_buy_img = new GraphicsPixmapItem(get_img("house"), view->get_scene(), shop_img_pos["house"]);
        try_to_buy_img->add_img();
    }
}

void Game::try_to_buy_field(){
    if(current_stat["gold"] >= building_price["field"]){
        try_to_buy = FIELD;
        try_to_buy_img = new GraphicsPixmapItem(get_img("field"), view->get_scene(), shop_img_pos["field"]);
        try_to_buy_img->add_img();
    }
}

void Game::try_to_buy_farm(){
    if(current_stat["gold"] >= building_price["farm"]){
        try_to_buy = FARM;
        try_to_buy_img = new GraphicsPixmapItem(get_img("farm"), view->get_scene(), shop_img_pos["farm"]);
        try_to_buy_img->add_img();
    }
}


void Game::set_max_citizen(int x){
    max_citizen = x;
    surpopulation = max_citizen * 1.2;
    top_info["nb_citizen"]->set_value_of_a_son(x, "max_citizen");
    if(nb_citizen <= max_citizen){
        top_info["nb_citizen"]->set_text_color(QColor(0, 0, 0));
    }
}

int Game::get_max_citizen(){
    return max_citizen;
}

template <typename T>
void Game::remove_elt(std::vector<T> *vec, T elt){
    for(unsigned int i=0; i<vec->size(); i++){
        if((*vec)[i] == elt){
            vec->erase(vec->begin() + i);
            break;
        }
    }
}


void Game::sold_building(){
    if(current_open_setting.building->type == FIELD){
        remove_elt(&field_vec, current_open_setting.building->building.field);
    }else if(current_open_setting.building->type == SHOP){
        remove_elt(&shop_vec, current_open_setting.building->building.shop);
    }else if(current_open_setting.building->type == HOUSE){
        remove_elt(&house_vec, current_open_setting.building->building.house);
    }else{
        remove_elt(&farm_vec, current_open_setting.building->building.farm);
    }
    apply_method_0(current_open_setting.building, &Building::sold);
    current_open_setting = {nullptr, nullptr};
}

void Game::increase_gold(float x){
    current_stat["gold"] += x;
    top_info["nb_gold"]->set_value(static_cast<int>(current_stat["gold"]));
    if(current_stat["gold"] < gold_limit){
        end_game("Lost by economic crisis ! Wanna restart ?");
    }
}

void Game::kik_workers(int x){
    nb_worker -= x;
    nb_unemployed += x;
    top_info["nb_worker"]->set_value(nb_worker);
    top_info["nb_non_worker"]->set_value(nb_unemployed);
}

void Game::lvl_up(){
    int price = apply_method_0(current_open_setting.building, &Building::get_price_to_up);
    if(current_stat["gold"] >= price){
        increase_gold(-price);
        apply_method_0(current_open_setting.building, &Building::lvl_up);
        update_stat();
    }
}

void Game::end_game(QString lost_type){
    menu->change_menu_info(lost_type);
    menu->return_to_menu();
}

Xy *Game::get_screen_size(){
    return &screen_size; 
}

void Game::reverse_current_setting(){
    current_open_setting.setting = current_open_setting.setting->reverse();
}

void Game::open_rules(){
    rules->open();
    citizen_bar->stop_load();   
    pause = true;
}

void Game::close_rules(){
    rules->close();
    if(!freez_img->is_open()){
        pause = false;
        citizen_bar->load();
    }
}
template <typename K, typename V>
void free_map(std::map<K, V> *map){
    std::vector<K> s;
    for(auto el: (*map)){
        delete (*map)[el.first];
        s.push_back(el.first);
    }
    for(unsigned int i = 0; i<s.size(); i++){
        map->erase(s[i]);
    }
}

template <typename T>
void free_vec(std::vector<T> *vec){
    while(vec->size() != 0){
        delete (*vec)[0];  
        vec->erase(vec->begin());
    }
}

