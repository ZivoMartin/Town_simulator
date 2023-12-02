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

protected:
    int nb_worker = 0;
    int lvl = 0;
    
};

#endif