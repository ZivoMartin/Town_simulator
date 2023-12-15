#ifndef tab_info_safe
#define tab_info_safe

#include "info_zone.h"

class TabInfo{

public:
    TabInfo(Game *game, Xy dim, Xy pos, Xy case_size, std::string name);
    ~TabInfo();

    void set_color(Xy coord, QColor color);
    void set_value(Xy coord, float value);
    void set_base_text(Xy coord, QString new_txt);
    float get_value(Xy coord);
    void set_text_size(Xy coord, int x);
    std::string get_name();
    void decal_txt(Xy coord, Xy decal);

    void add();
    void remove();
    void set_pos(Xy pos);
    Xy get_pos();
    
private:
    Game *game;
    std::string name;
    Xy dim; 
    Xy pos; 
    Xy case_size;
    std::vector<std::vector<InfoZone *>> tab_info;

};



#endif


//alouer de types de tableaux, dans l'allocation de shop remplir les deux dernieres lignes ne figurant pas dans house, remplir le reste dasn common value a
//partir des tableaux en attribut.