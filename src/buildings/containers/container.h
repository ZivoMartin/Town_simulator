#ifndef container_safe
#define container_safe

#include "../building.h"

class Container : public Building{

public:
    Container(QPixmap *image, Game *game, Xy coord);
    ~Container();
    void init_reverse() override;
    void init_personnal_value() override;
    bool add_worker() override;
    bool pull_worker() override;
    float get_efficiency() override;

private:

};


#endif