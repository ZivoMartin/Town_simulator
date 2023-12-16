#ifndef safe_building
#define safe_building

#include "../image/GraphicsPixmapItem.h"

class Setting;

class Building : public GraphicsPixmapItem{

public:
    Building(QPixmap *image, Game *game, Xy coord);
    ~Building();
    void set_worker(int x);
    void level_up();
    int get_level();
    int get_nb_worker();
    Xy *get_origin_pos();
    Xy *get_current_pos();
    void drag(Xy new_pos);
    Xy get_size();
    void set_origin_pos(Xy new_pos);
    virtual float get_efficiency();
    virtual void clicked();
    virtual bool add_worker() = 0;
    virtual bool pull_worker() = 0;
    virtual void init_stat() = 0;
    virtual void init_reverse() = 0;
    int get_price_to_up();
    void sold();
    void lvl_up();
    void init_common_value();
    virtual void init_personnal_value() = 0;
    void init_setting(Xy coord);

protected:
    Game *game;
    int nb_worker = 0;
    int lvl = 0;
    Xy origin_pos;
    Setting *setting;
    build_tab_case *setting_union;
    int lvl_max = 4;
    int nb_line;
    std::string type;
    
    std::vector<int> max_worker;
    std::vector<float> value_per_worker;
    std::vector<int> value_for_sold;
    std::vector<int> price_to_up;


};

#endif