#ifndef safe_struct
#define safe_struct

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

class Field;
class House;
class Shop;
class InfoZone;
class Setting;

struct Xy{
    int x;
    int y;
};

union union_building{
    Shop *shop;
    House *house;
    Field *field;
};

enum type_building{
    SHOP,
    HOUSE,
    FIELD,
    EMPTY
};

struct build_tab_case{
    type_building type;
    union_building building;
};

struct drag{
    bool dragging;
    build_tab_case item;
};

enum form_type{
    RECT,
    CIRCLE
};

union form{
    QGraphicsEllipseItem *circle;
    QGraphicsRectItem *rect;
};

struct text_info_bg{
    form_type type;
    form bg;
};

struct current_setting{
    build_tab_case *building;
    Setting *setting;
};

#endif