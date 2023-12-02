#ifndef safe_game
#define safe_game

#include <QMainWindow>
#include <random>
#include <iostream>
#include <QPixmap>
#include <QColor>
#include "image/GraphicsPixmapItem.h"
#include "view/GraphicsView.h"
#include "buildings/field.h"
#include "buildings/shop.h"
#include "buildings/house.h"

#define MAP_WIDTH 10000
#define MAP_HEIGHT 10000
#define CASE_SIZE 20



class Game : public QMainWindow{

public: 
    Game(GraphicsView *view);
    ~Game();
    int get_iter();

    void load_images();

    QPixmap *get_img(std::string img);
    GraphicsView *get_view();
    void setup_scene();

private:
    GraphicsView *view;
    unsigned int iter = 0;
    std::map<std::string, QPixmap*> images_map;
    std::vector<GraphicsPixmapItem*> field_vec;
    std::vector<std::vector<build_tab_case>> map_tab;
    QColor *background_color;
};

int random(int min, int max);
int get_dist(Xy *coord1, Xy *coord2);

#endif
