#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <random>
#include <iostream>
#include <QPixmap>
#include <QColor>
#include <QString>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QColor>
#include <QGuiApplication>
#include <QScreen>
#include <QApplication>
#include "image/GraphicsPixmapItem.h"
#include "view/GraphicsView.h"
#include "buildings/generators/field.h"
#include "buildings/generators/shop.h"
#include "buildings/containers/house.h"
#include "buildings/containers/farm.h"
#include "info_zone/info_zone.h"
#include "menu/menu.h"
#include "src/common_functions/common_functions.h"
#include "loading_bar/loading_bar.h"

#define CASE_SIZE 15
#define FIELD_WIDTH 105
#define FIELD_HEIGHT 105
#define SHOP_WIDTH 105
#define SHOP_HEIGHT 105
#define HOUSE_WIDTH 105
#define HOUSE_HEIGHT 105
#define FARM_HEIGHT 130
#define FARM_WIDTH 130
#define BASE_CITIZEN 10
#define BASE_FOOD 100
#define BASE_GOLD 100
#define BUILDING_ICON_WIDTH 105
#define BUILDING_ICON_HEIGHT 105


class Game : public QMainWindow{

public: 
    Game(QApplication *app, GraphicsView *view);
    ~Game();
    void play();
    void init_game();
    int get_iter();
    void screen_clicked(Xy coord_click);

    void load_images();
    void load_colors();
    void setup_scene();
    QPixmap *get_img(std::string img);
    GraphicsView *get_view();
    Xy *get_img_size(std::string img);
    Xy coord_to_tab(Xy *entry);
    Xy tab_to_coord(Xy *entry);
    bool create_new_building(std::string type, Xy pos);
    template <typename T> void new_building(T *new_building, void (Game::*f)(Xy, T*));
    template <typename T, typename G> G apply_method_1(build_tab_case *building, G (Building::*f)(T), T arg);
    template <typename G> G apply_method_0(build_tab_case *building, G (Building::*f)());
    template <typename T> void remove_elt(std::vector<T> *vec, T elt);
    void erase_zone(Xy *pos, Xy *s);
    void set_case_field(Xy pos, Field *field);
    void set_case_shop(Xy pos, Shop *shop);
    void set_case_house(Xy pos, House *house);
    void set_case_farm(Xy pos, Farm *farm);
    void set_case_empty(Xy pos);
    build_tab_case *get_map_tab_case(Xy pos);
    int convert_one_dim(Xy *pos);
    bool is_empty_place(Xy *pos, Xy *size);
    bool its_dragged_item_case(Xy pos);
    void correct_pos(Xy *tab_pos, Xy *size);
    bool is_dragging();
    void click_release(Xy stop_pos);
    void mouse_move(Xy pos);
    void build_info_bubble();
    void update_info();
    Xy *get_size_setting_building();
    QColor get_color(std::string color);
    void set_current_setting(Setting *setting, build_tab_case *building);
    void close_current_setting();
    void erase_button(PushButton *button);
    void add_button(PushButton *new_button);
    bool its_a_button_click(Xy *pos);
    void open_shop();
    void add_worker();
    void remove_worker();
    void update_food_ratio();
    void update_gold_ratio();
    void try_to_buy_shop();
    void try_to_buy_house();
    void try_to_buy_field();
    void try_to_buy_farm();
    void set_max_citizen(int x);
    int get_max_citizen();
    void sold_building();
    void increase_gold(float x);
    void kik_workers(int x);
    void lvl_up();
    void end_game(QString lost_type);
    void reset();
    void clean_building();
    void build_shop();
    void init_info_bubble();
    void start();
    void start_signal();
    void reverse_current_setting();
    void open_rules();
    void close_rules();
    Xy *get_screen_size();
    void freez_game();
    void add_citizen();
    void citizen_bar_complete();
    int get_max_food();
    void set_max_food(int x);
    void update_max_citizen();
    void update_max_food();
    void update_stat();
    void open_param();
    void close_param();
    void build_param();
    void quit_app();
    void kill_a_citizen();
    void speed_down();
    void speed_up();
    void return_to_menu();
    int get_speed_frame();
    
private:
    GraphicsView *view;
    QApplication *app;
    unsigned int iter;
    
    std::map<std::string, QPixmap*> images_map;
    std::map<std::string, Xy> dim_img_map;
    std::map<std::string, QColor> color_map;
    std::map<std::string, InfoZone*> top_info;
    std::map<int, build_tab_case> map_tab;
    std::map<std::string, float> current_stat;
    std::map<std::string, int> building_price;
    std::map<std::string, Xy> shop_img_pos;

    std::vector<Field*> field_vec;
    std::vector<House*> house_vec;
    std::vector<Shop*> shop_vec;
    std::vector<Farm*> farm_vec;
    std::vector<PushButton*> button_vec;
    
    drag dragging;
    QColor *background_color;
    Xy info_bubble_dims = {180, 70};
    Xy map_case_dim;
    Xy size_settings_building = {400, 230};
    current_setting current_open_setting = {nullptr, nullptr};
    Xy screen_size;
    Xy shop_setting_size = {900, 250};
    Setting *shop_menu_setting;
    GraphicsPixmapItem *bg_img;
    type_building try_to_buy = EMPTY;
    GraphicsPixmapItem *try_to_buy_img = nullptr;
    Menu *menu;
    PushButton *shop_button;
    Setting *rules;
    PushButton *open_rules_button;
    GraphicsPixmapItem *freez_img;
    LoadingBar *citizen_bar;
    Setting *param;


    bool pause = false;
    int frame_speed = 20;
    int price_to_add = 25;
    int nb_citizen;
    int nb_worker;
    int nb_unemployed;
    int max_citizen;
    int surpopulation;
    int gold_limit;
    int max_food = 0;

    float factor_citizen_ratio = 800;

    QString rules_txt = "It's a city management simulation, where the player has \nthree things to manage: money, which allows them to build, food, which keeps the\n inhabitants alive, and the number of inhabitants. The player has three indicators: food gained per second, number of inhabitants added per second, and \nmoney gained per second.\nThere are 3 categories of buildings:\nThe field: It increases the food gained per second. If there is no food, one inhabitant dies per second.\nThe supermarket: It generates money. If the money goes below a certain negative value (-100), the game ends.\nThe houses: They accommodate the inhabitants. Based on the maximum number of inhabitants the city can house, an \noverpopulation value greater than the maximum number of inhabitants is calculated. If this value is exceeded, the game is lost.\nIt is allowed to exceed the limit, but time will be counted down before defeat, serving as a warning.\nThe farm increases the amount of food that can be stored!\nIn each building, there is a maximum number of people who can work. Each additional inhabitant in a building \nincreases the resources that building generates per second. Each building can be upgraded to increase its capacity to \naccommodate more inhabitants as well as\nthe efficiency of each inhabitant within the building. For houses, it\nsimply increases the number of inhabitants that can be housed inside. The more inhabitants there are, the more food is required, and the more buildings there are, the lower the gold per second ratio becomes.\nThe goal of the game is to have as many inhabitants as possible.";
};

#endif
