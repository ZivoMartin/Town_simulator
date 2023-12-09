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
    float get_efficiency();
    virtual void clicked();
    virtual bool add_worker() = 0;
    virtual bool pull_worker() = 0;

protected:
    Game *game;
    int nb_worker = 0;
    float value_per_worker = 0;
    int lvl = 0;
    Xy origin_pos;
    Setting *setting;
    build_tab_case *setting_union;
};

#endif