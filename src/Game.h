#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <random>
#include <iostream>
#include <QPixmap>
#include <QColor>
#include <QString>
#include <QTimer>
#include "image/GraphicsPixmapItem.h"
#include "view/GraphicsView.h"
#include "buildings/field.h"
#include "buildings/shop.h"
#include "buildings/house.h"

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


class Game : public QMainWindow{

public: 
    Game(GraphicsView *view);
    ~Game();
    void play();
    void init_game();
    int get_iter();
    void screen_clicked(Xy coord_click);

    void load_images();
    void setup_scene();
    QPixmap *get_img(std::string img);
    GraphicsView *get_view();
    Xy *get_img_size(std::string img);
    Xy coord_to_tab(Xy *entry);
    Xy tab_to_coord(Xy *entry);
    void create_new_building(std::string type, Xy pos);
    template <typename T> void new_building(T *new_building, void (Game::*f)(Xy, T*));
    template <typename T> void free_vec(std::vector<T> vec);
    void erase_zone(Xy *pos, Xy *s);
    void set_case_field(Xy pos, Field *field);
    void set_case_shop(Xy pos, Shop *shop);
    void set_case_house(Xy pos, House *house);
    void set_case_empty(Xy pos);
    build_tab_case *get_map_tab_case(Xy pos);
    int convert_one_dim(Xy *pos);
    bool is_empty_place(Xy *pos, Xy *size);
    bool is_dragging();
    void click_release(Xy stop_pos);
    void mouse_move(Xy pos);
   template <typename T, typename G> G apply_method(build_tab_case *building, G (Building::*f)(T), T arg);
   template <typename G> G apply_get_method(build_tab_case *building, G (Building::*f)());


private:
    GraphicsView *view;
    unsigned int iter = 0;
    
    std::map<std::string, QPixmap*> images_map;
    std::map<std::string, Xy> dim_img_map;
    std::map<int, build_tab_case> map_tab;

    std::vector<Field*> field_vec;
    std::vector<House*> house_vec;
    std::vector<Shop*> shop_vec;
    
    drag dragging;
    
    QColor *background_color;
    Xy map_case_dim;
    
};

int random(int min, int max);
int get_dist(Xy *coord1, Xy *coord2);

#endif
