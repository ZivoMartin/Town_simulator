#ifndef safe_building
#define safe_building

#include "../image/GraphicsPixmapItem.h"

class Building : public GraphicsPixmapItem{

public:
    Building(QPixmap *image, QGraphicsScene *scene, Xy coord);
    ~Building();
    void set_worker(int x);
    void level_up();
    int get_level();
    int get_nb_worker();
    Xy *get_origin_pos();
    void drag(Xy new_pos);
    Xy get_size();
    void set_origin_pos(Xy new_pos);
    virtual int get_efficiency();

protected:
    int nb_worker = 0;
    int value_per_worker = 0;
    int lvl = 0;
    Xy origin_pos;
    
};

#endif