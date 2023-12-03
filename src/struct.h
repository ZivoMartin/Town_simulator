#ifndef safe_struct
#define safe_struct

class Field;
class House;
class Shop;

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


#endif