#ifndef safe_setting
#define safe_setting

#include <iostream>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QApplication>

#include "../buildings/generators/field.h"
#include "../buildings/containers/house.h"
#include "../buildings/generators/shop.h"
#include "../struct.h"
#include "../button/button.h"
#include "../info_zone/tab_info.h"

class Setting: public QGraphicsRectItem{

public:    
    Setting(Game *game, Xy pos, Xy size, Setting *reverse);
    ~Setting();
    void open();
    void close();
    void set_pos(Xy pos);
    Xy get_pos();
    void add_button(PushButton *button);
    void erase_button(std::string name);
    void add_info_zone(InfoZone *new_zone);
    void erase_info_zone(std::string name);
    void add_img(GraphicsPixmapItem *new_img);
    void erase_img(GraphicsPixmapItem *img);
    void add_tab_info(TabInfo *new_tab);
    InfoZone *get_info_zone(std::string name);
    PushButton *get_button(std::string name);
    TabInfo *get_tab_info(std::string name);
    bool get_is_open();
    Setting *get_reverse();
    void set_reverse_button();
    Setting *reverse();
    void switch_have_to_delete_reverse();
    void set_color(QColor new_color);
    bool is_it(Xy *coord);

private:
    PushButton *close_button;
    PushButton *reverse_button = nullptr;
    Xy size;
    Game *game;
    QBrush *brush;
    QGraphicsScene *scene;
    Xy pos;

    std::map<std::string, PushButton*> button_map;
    std::map<std::string, InfoZone*> infozone_map;
    std::map<std::string, TabInfo*> tab_info_map;
    std::vector<GraphicsPixmapItem*> static_img_vec;
    
    
    bool is_open = false;
    bool reversed = false;
    Setting *reverse_setting;
    bool have_to_delete_reverse = true;
};

#endif