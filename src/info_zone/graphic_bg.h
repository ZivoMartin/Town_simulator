#ifndef graphic_bg_safe
#define graphic_bg_safe

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QColor>
#include "../struct.h"

class GraphicBg{

public:
    GraphicBg(form_type type, Xy pos, Xy size, QColor color, QGraphicsScene *scene);
    ~GraphicBg();
    void add();
    void remove();
    void set_pos(Xy pos);
    form_type get_type();
    void set_color(QColor color);

private:
    text_info_bg bg_union;
    Xy pos;
    Xy size;
    QColor color;
    QGraphicsScene *scene;
    QBrush *brush;
};


#endif