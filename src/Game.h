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
#include "image/GraphicsPixmapItem.h"
#include "view/GraphicsView.h"
#include "buildings/field.h"
#include "buildings/shop.h"
#include "buildings/house.h"
#include "info_zone/info_zone.h"
#include "settings_building/settings.h"
#include "common_functions/common_functions.h"


#define CASE_SIZE 15
#define FIELD_WIDTH 105
#define FIELD_HEIGHT 105
#define SHOP_WIDTH 105
#define SHOP_HEIGHT 105
#define HOUSE_WIDTH 105
#define HOUSE_HEIGHT 105
#define FRAME_SPEED 20
#define BASE_CITIZEN 10
#define BASE_FOOD 100
#define BASE_GOLD 100


class Game : public QMainWindow{

public: 
    Game(GraphicsView *view);
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
    void create_new_building(std::string type, Xy pos);
    template <typename T> void new_building(T *new_building, void (Game::*f)(Xy, T*));
    template <typename T, typename G> G apply_method_1(build_tab_case *building, G (Building::*f)(T), T arg);
    template <typename G> G apply_method_0(build_tab_case *building, G (Building::*f)());
    void erase_zone(Xy *pos, Xy *s);
    void set_case_field(Xy pos, Field *field);
    void set_case_shop(Xy pos, Shop *shop);
    void set_case_house(Xy pos, House *house);
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
    
private:
    GraphicsView *view;
    unsigned int iter = 0;
    
    std::map<std::string, QPixmap*> images_map;
    std::map<std::string, Xy> dim_img_map;
    std::map<std::string, QColor> color_map;
    std::map<std::string, InfoZone*> top_info;
    std::map<int, build_tab_case> map_tab;
    std::map<std::string, float> current_stat;

    std::vector<Field*> field_vec;
    std::vector<House*> house_vec;
    std::vector<Shop*> shop_vec;
    std::vector<PushButton*> button_vec;

    drag dragging;
    QColor *background_color;
    Xy info_bubble_dims = {180, 70};
    Xy map_case_dim;
    Xy size_settings_building = {400, 200};
    current_setting current_open_setting = {nullptr, nullptr};
    Xy screen_size;
    Xy shop_setting_size = {800, 300};
    Setting *shop_menu_setting;
    QGraphicsPixmapItem *bg_img;

    int nb_citizen = BASE_CITIZEN;
    int nb_worker = 0;
    int nb_unemployed = BASE_CITIZEN;
    int max_citizen = 14;

    float factor_citizen_ratio = 800;
};

#endif
