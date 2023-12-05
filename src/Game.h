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
#include "image/GraphicsPixmapItem.h"
#include "view/GraphicsView.h"
#include "buildings/field.h"
#include "buildings/shop.h"
#include "buildings/house.h"
#include "info_zone/info_zone.h"
#include "button/button.h"
#include "settings_building/settings.h"


#define MAP_WIDTH 10000
#define MAP_HEIGHT 10000
#define CASE_SIZE 20
#define FIELD_WIDTH 100
#define FIELD_HEIGHT 100
#define SHOP_WIDTH 100
#define SHOP_HEIGHT 100
#define HOUSE_WIDTH 100
#define HOUSE_HEIGHT 100
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
    template <typename T> void free_vec(std::vector<T> vec);
    template <typename T, typename G> G apply_method(build_tab_case *building, G (Building::*f)(T), T arg);
    template <typename G> G apply_get_method(build_tab_case *building, G (Building::*f)());
    template <typename K, typename V> void free_map(std::map<K, V> map);
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
    Xy *get_size_setting();
    QColor get_color(std::string color);

private:
    GraphicsView *view;
    unsigned int iter = 0;
    
    std::map<std::string, QPixmap*> images_map;
    std::map<std::string, Xy> dim_img_map;
    std::map<std::string, QColor> color_map;
    std::map<std::string, InfoZone*> top_info;
    std::map<int, build_tab_case> map_tab;

    std::vector<Field*> field_vec;
    std::vector<House*> house_vec;
    std::vector<Shop*> shop_vec;
    
    drag dragging;
    QColor *background_color;
    Xy info_bubble_dims = {180, 70};
    Xy map_case_dim = {MAP_WIDTH/CASE_SIZE, MAP_HEIGHT/CASE_SIZE};
    Xy size_settings = {400, 200};
};

int random(int min, int max);
int get_dist(Xy *coord1, Xy *coord2);

#endif
