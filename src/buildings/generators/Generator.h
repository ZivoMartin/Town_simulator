#ifndef generator_safe
#define generator_safe

#include "../building.h"


class Generator : public Building{

public:

    Generator(QPixmap *image, Game *game, Xy coord);
    ~Generator();
    void init_reverse() override;
    void init_personnal_value() override;
    
private:

};

#endif