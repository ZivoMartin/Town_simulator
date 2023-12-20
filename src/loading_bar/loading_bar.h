#ifndef loading_bar_safe
#define loading_bar_safe

#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QBrush>
#include "../struct.h"
#include "../info_zone/info_zone.h"


class Game;

class LoadingBar : public QGraphicsRectItem{

public:
    LoadingBar(Game *game, Xy pos, Xy size, void (Game::*f)(), QString txt);
    ~LoadingBar();
    
    void load();
    void set_ratio(int percent_value);
    void stop_load();
    void reset_load();

    void add();
    void remove();

private:
    Game *game;
    Xy pos;
    Xy size;
    QGraphicsRectItem *bar;
    QGraphicsScene *scene;
    InfoZone *txt;
    float ratio;
    float state = 0;
    bool is_open = false;
    QBrush *load_bar_brush;
    bool stop = false;

    void (Game::*achievement)();

};


#endif