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
#define FRAME_SPEED 20
#define BASE_CITIZEN 10
#define BASE_FOOD 100
#define BASE_GOLD 100
#define BUILDING_ICON_WIDTH 105
#define BUILDING_ICON_HEIGHT 105


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
    
private:
    GraphicsView *view;
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
    bool pause = false;

    int price_to_add = 25;
    int nb_citizen;
    int nb_worker;
    int nb_unemployed;
    int max_citizen;
    int surpopulation;
    int gold_limit;
    int max_food = 0;

    float factor_citizen_ratio = 800;

    QString rules_txt = "Principe du jeu:\nC'est une simulation de gestion de ville, le joueur à trois choses à gérer, l'argent qui lui permet de construire, la nourriture qui lui permet de \ngarder ses habitants en vie, et le nombre d'habitant. Le joueur a donc trois indices, nourriture gagnée par seconde, nombre d'habitants en plus par seconde,\net argent gagnée par seconde.\n\nIl éxiste 3 catégories de batiments:\n    -Le champs: Il permet d'augmenter la nourriture gagnée par seconde, s'il n'y a plus de nourriture un habitant meurt par seconde.\n  -La superette: Elle permet de générer de l'argent. Si l'argent dépasse une certaine valeur négative (-100), la partie est finie.\n  -Les maison: Elles permettent de loger les habitants. En fonction du nombre maximum d'habitant pouvant peupler la ville, une valeur de surpopulation\n  superieur à celle d'habitant maximum est donnée, si cette valeur est depassée, la partie est perdue.\n  Il est donc autorisé de depasser la limite mais le temps sera alors compté avant la défaite, c'est une sorte d'avertissement.\n    -La ferme permet d'augmenter la quantitée de food stockable !\n\nDans chaque batiment il peut il y a voir un nombre maximum de personne qui y travaille, chaque habitant en plus dans le batiment augmente les ressources\nque ce batiment génère par seconde. Chaque batiment peut etre amelioré pour augmenter sa capacitée à accueilir des habitants ainsi que le rendement d'un habitant \ndans le batiment. Pour les maisons ca augmente simplement le nombre d'habitant logable à l'interieur. Pus il y a d'habitant, plus les besoins en nourriture \naugmentent, plus il y à de bâtiments plus le ratio en gold par seconde baisse.\n\nLe but du jeu est donc d'avoir le plus d'habitant possible.";
};

#endif
