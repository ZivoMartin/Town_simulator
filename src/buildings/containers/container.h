#ifndef container_safe
#define container_safe

#include "../building.h"

class Container : public Building{

public:
    Container(QPixmap *image, Game *game, Xy coord);
    ~Container();
    void init_reverse() override;
    void init_personnal_value() override;

private:

};


#endif