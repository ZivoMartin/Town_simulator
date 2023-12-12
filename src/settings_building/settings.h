#ifndef safe_setting
#define safe_setting

#include <iostream>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QApplication>

#include "../buildings/field.h"
#include "../buildings/house.h"
#include "../buildings/shop.h"
#include "../struct.h"
#include "../button/button.h"
#include "../info_zone/info_zone.h"

class Setting: public QGraphicsRectItem{

public:    
    Setting(Game *game, Xy pos, Xy size, Setting *reverse);
    ~Setting();
    void open();
    void close();
    void set_pos(Xy pos);
    void add_button(PushButton *button);
    void erase_button(std::string name);
    void add_info_zone(InfoZone *new_zone);
    void erase_info_zone(std::string name);
    void add_img(GraphicsPixmapItem *new_img);
    void erase_img(GraphicsPixmapItem *img);
    InfoZone *get_info_zone(std::string name);
    PushButton *get_button(std::string name);
    bool get_is_open();
    Setting *get_reverse();
    void set_reverse_button();
    Setting *reverse();
    void switch_have_to_delete_reverse();

private:
    PushButton *close_button;
    PushButton *reverse_button;
    Xy size;
    Game *game;
    QBrush *brush;
    QGraphicsScene *scene;
    Xy pos;
    std::map<std::string, PushButton*> button_map;
    std::map<std::string, InfoZone*> infozone_map;
    std::vector<GraphicsPixmapItem*> static_img_vec;
    bool is_open = false;
    bool reversed = false;
    Setting *reverse_setting;
    bool have_to_delete_reverse = true;
};

#endif